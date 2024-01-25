
.PHONY: all ipt modules modules_install install clean
.PHONY: clean_modules distclean dkms dkms_install dkms_deb dkms_rpm pkg testnl
.PHONY: dkms_clean pkg_clean

all:
	$(MAKE) -C ipt
	+$(MAKE) -C src

ipt:
	$(MAKE) -C ipt
modules:
	$(MAKE) -C src
modules_install:
	$(MAKE) -C src modules_install
install:
	$(MAKE) -C ipt install
clean:
	$(MAKE) -C src clean
	$(MAKE) -C ipt clean
clean_modules:
	$(MAKE) -C src clean
	$(MAKE) -C src distclean
distclean:
	$(MAKE) clean
	$(MAKE) -C src distclean

dkms:
	$(MAKE) -C dkms all
dkms_install:
	$(MAKE) -C dkms install
dkms_clean:
	$(MAKE) -C dkms clean
dkms_deb:
	$(MAKE) -C dkms dkms_deb
dkms_rpm:
	$(MAKE) -C dkms dkms_rpm

pkg:
	$(MAKE) -C packages/lib_ipt/deb all
pkg_clean:
	$(MAKE) -C packages/lib_ipt/deb clean

