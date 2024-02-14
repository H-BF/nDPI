DKMS_PACKAGE_NAME="xt_ndpi"
DKMS_PACKAGE_VERSION="4.9"
DKMS_DIR = dkms_dir
DKMS_SETUP_DIR = /usr/src/$(DKMS_PACKAGE_NAME)-$(DKMS_PACKAGE_VERSION)

file_find_provides="/usr/lib/dkms/find-provides"

.PHONY: all install clean dkms-deb dkms-rpm

all:
	if [ ! -d "$(DKMS_DIR)" ]; then \
		mkdir -p $(DKMS_DIR)/ndpi-netfilter; \
	fi
	cp dkms.conf $(DKMS_DIR)
	cp xt_ndpi-dkms-mkrpm.spec $(DKMS_DIR)
	cp -r ../../src $(DKMS_DIR)
	cp -r ../libre $(DKMS_DIR)/ndpi-netfilter
	cp -r ../src $(DKMS_DIR)/ndpi-netfilter
	cp ../Makefile $(DKMS_DIR)/ndpi-netfilter

	if [ ! -f "$(file_find_provides)" ]; then \
		if ! [ "$(shell id -u)" -eq 0 ]; then \
			sudo install ./find-provides /usr/lib/dkms/; \
		else \
			install ./find-provides /usr/lib/dkms/; \
		fi \
	fi

	$(MAKE) -C $(DKMS_DIR)/ndpi-netfilter/src clean
	$(MAKE) -C $(DKMS_DIR)/ndpi-netfilter/src distclean

	if [ ! -d "$(DKMS_SETUP_DIR)" ]; then \
		if ! [ "$(shell id -u)" -eq 0 ]; then \
			sudo mkdir $(DKMS_SETUP_DIR); \
		else \
			mkdir $(DKMS_SETUP_DIR); \
		fi \
	fi

	if ! [ "$(shell id -u)" -eq 0 ]; then \
		sudo cp -r $(DKMS_DIR)/* $(DKMS_SETUP_DIR); \
		sudo dkms build -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) || exit 1; \
	else \
		cp -r $(DKMS_DIR)/* $(DKMS_SETUP_DIR); \
		dkms build -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) || exit 1; \
	fi

install:
	if ! [ "$(shell id -u)" -eq 0 ]; then \
		sudo dkms install -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) || exit 1; \
	else \
		dkms install -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) || exit 1; \
	fi \

clean:
	rm -rf dkms_dir/
	if ! [ "$(shell id -u)" -eq 0 ]; then \
		sudo dkms remove -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) --all; \
	else \
		dkms remove -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION) --all; \
	fi

dkms-deb:
	if ! [ "$(shell id -u)" -eq 0 ]; then \
		sudo dkms mkdeb -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION); \
	else \
		dkms mkdeb -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION); \
	fi \

dkms-rpm:
	if ! [ "$(shell id -u)" -eq 0 ]; then \
		sudo dkms mkrpm -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION); \
	else \
		dkms mkrpm -m $(DKMS_PACKAGE_NAME) -v $(DKMS_PACKAGE_VERSION); \
	fi \

