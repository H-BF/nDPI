
.PHONY: all clean

all:
	files_found=$$(find ../../../ipt/ -name "*.so"); \
	if [ ! -n "$$files_found" ]; then \
		$(MAKE) -C ../../../ipt; \
	fi
	mkdir -p ./debian/usr/lib/
	chmod 0755 -R ../../
	cp ../../../ipt/libxt_ndpi.so ./debian/usr/lib/
	dpkg-deb --build debian libxt-ndpi.deb

clean:
	find ./debian/usr/lib/ -type f \( -name \*.so \) | xargs -r rm
	rm -rf *.deb