all:
	# -fPIC: Pozisyondan bağımsız kod (Bellekte herhangi bir yere yüklenebilir)
	# -shared: Paylaşılan kütüphane oluştur
	# -ldl: Dynamic Linking kütüphanesini bağla
	gcc -Wall -fPIC -shared -o phantom.so phantom.c -ldl

clean:
	rm -f phantom.so
