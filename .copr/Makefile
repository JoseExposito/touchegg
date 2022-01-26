outdir  ?= rpmbuild/SRPMS

.PHONY: srpm
srpm:
	dnf install -y git
	mkdir -p rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS}
	tar -czvf rpmbuild/SOURCES/touchegg.tar.gz -C .. touchegg --transform s/^touchegg/touchegg-$$(git describe --tags --abbrev=0)/
	rpmbuild -D'_srcrpmdir $(outdir)' -bs rpm/touchegg.spec
