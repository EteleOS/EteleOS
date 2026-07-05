/*	$OpenBSD: smtpinctrl.c,v 1.1 2026/04/10 17:37:00 kettenis Exp $	*/
/*
 * Copyright (c) 2026 Mark Kettenis <kettenis@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>
#include <sys/malloc.h>

#include <machine/bus.h>
#include <machine/fdt.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_clock.h>
#include <dev/ofw/ofw_pinctrl.h>
#include <dev/ofw/fdt.h>

/* Registers. */
#define MFPR_PULL_SEL		(1U << 15)
#define MFPR_PULLUP_EN		(1U << 14)
#define MFPR_PULLDN_EN		(1U << 13)
#define MFPR_DRIVE_MASK		(0x7 << 10)
#define MFPR_DRIVE_SHIFT	10
#define MFPR_SPU		(1U << 3)
#define MFPR_AF_SEL_MASK	(0x7 << 0)
#define MFPR_AF_SEL_SHIFT	0

#define HREAD4(sc, reg)							\
	(bus_space_read_4((sc)->sc_iot, (sc)->sc_ioh, (reg)))
#define HWRITE4(sc, reg, val)						\
	bus_space_write_4((sc)->sc_iot, (sc)->sc_ioh, (reg), (val))

struct smtpinctrl_softc {
	struct device		sc_dev;
	bus_space_tag_t		sc_iot;
	bus_space_handle_t	sc_ioh;
	int			sc_node;
};

int	smtpinctrl_match(struct device *, void *, void *);
void	smtpinctrl_attach(struct device *, struct device *, void *);

const struct cfattach smtpinctrl_ca = {
	sizeof (struct smtpinctrl_softc), smtpinctrl_match, smtpinctrl_attach
};

struct cfdriver smtpinctrl_cd = {
	NULL, "smtpinctrl", DV_DULL
};

int	k1_pinctrl(uint32_t, void *);

int
smtpinctrl_match(struct device *parent, void *match, void *aux)
{
	struct fdt_attach_args *faa = aux;

	return OF_is_compatible(faa->fa_node, "spacemit,k1-pinctrl");
}

void
smtpinctrl_attach(struct device *parent, struct device *self, void *aux)
{
	struct smtpinctrl_softc *sc = (struct smtpinctrl_softc *)self;
	struct fdt_attach_args *faa = aux;

	if (faa->fa_nreg < 1) {
		printf(": no registers\n");
		return;
	}

	sc->sc_iot = faa->fa_iot;
	if (bus_space_map(sc->sc_iot, faa->fa_reg[0].addr,
	    faa->fa_reg[0].size, 0, &sc->sc_ioh)) {
		printf(": can't map registers\n");
		return;
	}
	sc->sc_node = faa->fa_node;

	printf("\n");

	clock_enable_all(sc->sc_node);

	pinctrl_register(sc->sc_node, k1_pinctrl, sc);
}

void
k1_config_pin(struct smtpinctrl_softc *sc, uint32_t pinmux, int bias, int ds)
{
	uint16_t func = pinmux & 0xffff;
	uint16_t pin = pinmux >> 16;
	bus_size_t offset = -1;
	uint32_t val;

	if (pin <= 85)
		offset = (pin + 1) * 4;
	if (pin >= 93 && pin <= 97)
		offset = (pin + 24) * 4;

	if (offset == -1) {
		printf("%s: unsupported pin %d\n", sc->sc_dev.dv_xname, pin);
		return;
	}

	val = HREAD4(sc, offset);

	/* Select function */
	val &= ~MFPR_AF_SEL_MASK;
	val |= (func << MFPR_AF_SEL_SHIFT);

	/* Set bias */
	if (bias != -1) {
		val &= ~(MFPR_PULL_SEL | MFPR_PULLUP_EN | MFPR_PULLDN_EN);
		val &= ~MFPR_SPU;
		val |= bias;
	}

	/* Set drive strength */
	if (ds != -1) {
		val &= ~MFPR_DRIVE_MASK;
		val |= (ds << MFPR_DRIVE_SHIFT);
	}

	HWRITE4(sc, offset, val);
}

int
k1_pinctrl(uint32_t phandle, void *cookie)
{
	struct smtpinctrl_softc *sc = cookie;
	uint32_t *pinmux;
	int node, child;
	int bias, ds;
	int i, len;

	node = OF_getnodebyphandle(phandle);
	if (node == 0)
		return -1;

	for (child = OF_child(node); child; child = OF_peer(child)) {
		len = OF_getproplen(child, "pinmux");
		if (len <= 0)
			continue;

		if (OF_getproplen(child, "input-schmitt") >= 0) {
			printf("%s: \"input-schmitt\" unsupported\n",
			    sc->sc_dev.dv_xname);
			continue;
		}
		if (OF_getproplen(child, "power-source") >= 0) {
			printf("%s: \"power-source\" unsupported\n",
			    sc->sc_dev.dv_xname);
			continue;
		}
		if (OF_getproplen(child, "slew-rate") >= 0) {
			printf("%s: \"slew-rate\" unsupported\n",
			    sc->sc_dev.dv_xname);
			continue;
		}

		/* Bias */
		bias = OF_getpropint(child, "bias-pull-up", -1);
		if (bias == -1) {
			if (OF_getpropbool(child, "bias-pull-down"))
				bias = MFPR_PULL_SEL | MFPR_PULLDN_EN;
			else if (OF_getpropbool(child, "bias-disable"))
				bias = 0;
		} else {
			if (bias == 1)
				bias = MFPR_SPU;
			bias |= MFPR_PULL_SEL | MFPR_PULLUP_EN;
		}

		/* Drive strength */
		ds = OF_getpropint(child, "drive-strength", -1);
		if (ds != -1) {
			/*
			 * Translate from mA to register value.
			 * Assume these are 1.8V pins for now; match
			 * exact values to prevent accidents.
			 */
			switch (ds) {
			case 11:
				ds = 0;
				break;
			case 21:
				ds = 2;
				break;
			case 32:
				ds = 4;
				break;
			case 42:
				ds = 6;
				break;
			default:
				printf("%s: unsupported drive strength %d\n",
				    sc->sc_dev.dv_xname, ds);
				break;
			}
		}

		pinmux = malloc(len, M_TEMP, M_WAITOK);
		OF_getpropintarray(child, "pinmux", pinmux, len);

		for (i = 0; i < len / sizeof(uint32_t); i++)
			k1_config_pin(sc, pinmux[i], bias, ds);

		free(pinmux, M_TEMP, len);
	}

	return -1;
}
