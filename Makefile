all: pub sub

pub:
	gcc -o pub ./publisher/pub.c ./common/common.c ./common/header.h -I ./common/ -lmosquitto -lssl -lcrypto

sub:
	gcc -o sub ./subscriber/sub.c ./common/common.c ./common/header.h -I ./common/ -lmosquitto -lssl -lcrypto

clean:
	rm -rf sub pub
