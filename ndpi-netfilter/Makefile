
.PHONY: all ipt modules modules-install install clean
.PHONY: clean-modules distclean dkms dkms-install dkms-deb dkms-rpm pkg testnl
.PHONY: dkms-clean pkg-clean

all:
	$(MAKE) -C ipt
	$(MAKE) -C src

ipt:
	$(MAKE) -C ipt
modules:
	$(MAKE) -C src
modules-install:
	$(MAKE) -C src modules_install
install:
	$(MAKE) -C ipt install
	$(MAKE) -C src modules_install
clean:
	$(MAKE) -C src clean
	$(MAKE) -C ipt clean
clean-modules:
	$(MAKE) -C src clean
	$(MAKE) -C src distclean
distclean:
	$(MAKE) clean
	$(MAKE) -C src distclean

dkms:
	$(MAKE) -C dkms all
dkms-install:
	$(MAKE) -C dkms install
dkms-clean:
	$(MAKE) -C dkms clean
dkms-deb:
	$(MAKE) -C dkms dkms-deb
dkms-rpm:
	$(MAKE) -C dkms dkms-rpm

pkg:
	$(MAKE) -C packages/lib_ipt/deb all
pkg-clean:
	$(MAKE) -C packages/lib_ipt/deb clean

