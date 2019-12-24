all clean :
	cd src && make $@
dist:
	cp ./src/dose2 ./
	zip -r "./dose2vampire_`git rev-parse --short HEAD`.zip" dose2 dose2.info data

