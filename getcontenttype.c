#include <stdio.h>
#include <string.h>

// Full Supported Content-Type according to Mozilla
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types

char* getContentType( char *path ) {
    int len;
    int temp = 1;
    char filename[512];
    char ext[16];
    // get filename
    while(temp < strlen(path)) {
      len = temp;
      temp += strcspn(path+temp+1, "/") + 1;
    }
    strcpy(filename, path+len+1);

    // get Extension
    if ( (len = strcspn(filename, ".")) != strlen(filename) ) {
      strcpy(ext, &filename[len]);
    } else {
        printf("Just Plain Text\n");
        return "Content-Type: text/plain\r\n\r\n";
    }

    printf("Extension: '%s'\n", ext);

    if (strcmp(ext, ".aac") == 0) {
        return "Content-Type: audio/aac\r\n\r\n";
    } else if (strcmp(ext, ".abw") == 0) {
        return "Content-Type: application/x-abiword\r\n\r\n";
    } else if (strcmp(ext, ".arc") == 0) {
        return "Content-Type: application/x-freearc\r\n\r\n";
    } else if (strcmp(ext, ".avi") == 0) {
        return "Content-Type: video/x-msvideo\r\n\r\n";
    } else if (strcmp(ext, ".azw") == 0) {
        return "Content-Type: application/vnd.amazon.ebook\r\n\r\n";
    } else if (strcmp(ext, ".bin") == 0) {
        return "Content-Type: application/octet-stream\r\n\r\n";
    } else if (strcmp(ext, ".bmp") == 0) {
        return "Content-Type: image/bmp\r\n\r\n";
    } else if (strcmp(ext, ".bz") == 0) {
        return "Content-Type: application/x-bzip\r\n\r\n";
    } else if (strcmp(ext, ".bz2") == 0) {
        return "Content-Type: application/x-bzip2\r\n\r\n";
    } else if (strcmp(ext, ".csh") == 0) {
        return "Content-Type: application/x-csh\r\n\r\n";
    } else if (strcmp(ext, ".css") == 0) {
        return "Content-Type: text/css\r\n\r\n";
    } else if (strcmp(ext, ".csv") == 0) {
        return "Content-Type: text/csv\r\n\r\n";
    } else if (strcmp(ext, ".doc") == 0) {
        return "Content-Type: application/msword\r\n\r\n";
    } else if (strcmp(ext, ".docx") == 0) {
        return "Content-Type: application/vnd.openxmlformats-officedocument.wordprocessingml.document\r\n\r\n";
    } else if (strcmp(ext, ".eot") == 0) {
        return "Content-Type: application/vnd.ms-fontobject\r\n\r\n";
    } else if (strcmp(ext, ".epub") == 0) {
        return "Content-Type: application/epub+zip\r\n\r\n";
    } else if (strcmp(ext, ".gz") == 0) {
        return "Content-Type: application/gzip\r\n\r\n";
    } else if (strcmp(ext, ".gif") == 0) {
        return "Content-Type: image/gif\r\n\r\n";
    } else if (strcmp(ext, ".htm") == 0 || strcmp(ext, ".html") == 0 ) {
        return "Content-Type: text/html\r\n\r\n";
    } else if (strcmp(ext, ".ico") == 0) {
        return "Content-Type: image/vnd.microsoft.icon\r\n\r\n";
    } else if (strcmp(ext, ".ics") == 0) {
        return "Content-Type: text/calendar\r\n\r\n";
    } else if (strcmp(ext, ".jar") == 0) {
        return "Content-Type: application/java-archive\r\n\r\n";
    } else if (strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".jpg") == 0 ) {
        return "Content-Type: image/jpeg\r\n\r\n";
    } else if (strcmp(ext, ".js") == 0) {
        return "Content-Type: text/javascript\r\n\r\n";
    } else if (strcmp(ext, ".json") == 0) {
        return "Content-Type: application/json\r\n\r\n";
    } else if (strcmp(ext, ".jsonld") == 0) {
        return "Content-Type: application/ld+json\r\n\r\n";
    } else if (strcmp(ext, ".mid") == 0 || strcmp(ext, ".midi") == 0 ) {
        return "Content-Type: audio/midi audio/x-midi\r\n\r\n";
    } else if (strcmp(ext, ".mjs") == 0) {
        return "Content-Type: text/javascript\r\n\r\n";
    } else if (strcmp(ext, ".mp3") == 0) {
        return "Content-Type: audio/mpeg\r\n\r\n";
    } else if (strcmp(ext, ".mp4") == 0) {
        return "Content-Type: video/mp4\r\n\r\n";
    } else if (strcmp(ext, ".mpeg") == 0) {
        return "Content-Type: video/mpeg\r\n\r\n";
    } else if (strcmp(ext, ".mpkg") == 0) {
        return "Content-Type: application/vnd.apple.installer+xml\r\n\r\n";
    } else if (strcmp(ext, ".odp") == 0) {
        return "Content-Type: application/vnd.oasis.opendocument.presentation\r\n\r\n";
    } else if (strcmp(ext, ".ods") == 0) {
        return "Content-Type: application/vnd.oasis.opendocument.spreadsheet\r\n\r\n";
    } else if (strcmp(ext, ".odt") == 0) {
        return "Content-Type: application/vnd.oasis.opendocument.text\r\n\r\n";
    } else if (strcmp(ext, ".oga") == 0) {
        return "Content-Type: audio/ogg\r\n\r\n";
    } else if (strcmp(ext, ".ogv") == 0) {
        return "Content-Type: video/ogg\r\n\r\n";
    } else if (strcmp(ext, ".ogx") == 0) {
        return "Content-Type: application/ogg\r\n\r\n";
    } else if (strcmp(ext, ".opus") == 0) {
        return "Content-Type: audio/opus\r\n\r\n";
    } else if (strcmp(ext, ".otf") == 0) {
        return "Content-Type: font/otf\r\n\r\n";
    } else if (strcmp(ext, ".png") == 0) {
        return "Content-Type: image/png\r\n\r\n";
    } else if (strcmp(ext, ".pdf") == 0) {
        return "Content-Type: application/pdf\r\n\r\n";
    } else if (strcmp(ext, ".php") == 0) {
        return "Content-Type: application/php\r\n\r\n";
    } else if (strcmp(ext, ".ppt") == 0) {
        return "Content-Type: application/vnd.ms-powerpoint\r\n\r\n";
    } else if (strcmp(ext, ".pptx") == 0) {
        return "Content-Type: application/vnd.openxmlformats-officedocument.presentationml.presentation\r\n\r\n";
    } else if (strcmp(ext, ".rar") == 0) {
        return "Content-Type: application/vnd.rar\r\n\r\n";
    } else if (strcmp(ext, ".rtf") == 0) {
        return "Content-Type: application/rtf\r\n\r\n";
    } else if (strcmp(ext, ".sh") == 0) {
        return "Content-Type: application/x-sh\r\n\r\n";
    } else if (strcmp(ext, ".svg") == 0) {
        return "Content-Type: image/svg+xml\r\n\r\n";
    } else if (strcmp(ext, ".swf") == 0) {
        return "Content-Type: application/x-shockwave-flash\r\n\r\n";
    } else if (strcmp(ext, ".tar") == 0) {
        return "Content-Type: application/x-tar\r\n\r\n";
    } else if (strcmp(ext, ".tif") == 0 || strcmp(ext, ".tiff") == 0 ) {
        return "Content-Type: image/tiff\r\n\r\n";
    } else if (strcmp(ext, ".ts") == 0) {
        return "Content-Type: video/mp2t\r\n\r\n";
    } else if (strcmp(ext, ".ttf") == 0) {
        return "Content-Type: font/ttf\r\n\r\n";
    } else if (strcmp(ext, ".txt") == 0) {
        return "Content-Type: text/plain\r\n\r\n";
    } else if (strcmp(ext, ".vsd") == 0) {
        return "Content-Type: application/vnd.visio\r\n\r\n";
    } else if (strcmp(ext, ".wav") == 0) {
        return "Content-Type: audio/wav\r\n\r\n";
    } else if (strcmp(ext, ".weba") == 0) {
        return "Content-Type: audio/webm\r\n\r\n";
    } else if (strcmp(ext, ".webm") == 0) {
        return "Content-Type: video/webm\r\n\r\n";
    } else if (strcmp(ext, ".webp") == 0) {
        return "Content-Type: image/webp\r\n\r\n";
    } else if (strcmp(ext, ".woff") == 0) {
        return "Content-Type: font/woff\r\n\r\n";
    } else if (strcmp(ext, ".woff2") == 0) {
        return "Content-Type: font/woff2\r\n\r\n";
    } else if (strcmp(ext, ".xhtml") == 0) {
        return "Content-Type: application/xhtml+xml\r\n\r\n";
    } else if (strcmp(ext, ".xls") == 0) {
        return "Content-Type: application/vnd.ms-excel\r\n\r\n";
    } else if (strcmp(ext, ".xlsx") == 0) {
        return "Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\r\n\r\n";
    } else if (strcmp(ext, ".xml") == 0) {
        return "Content-Type: application/xml\r\n\r\n";
    } else if (strcmp(ext, ".xul") == 0) {
        return "Content-Type: application/vnd.mozilla.xul+xml\r\n\r\n";
    } else if (strcmp(ext, ".zip") == 0) {
        return "Content-Type: application/zip\r\n\r\n";
    } else if (strcmp(ext, ".3gp") == 0) {
        return "Content-Type: video/3gpp\r\n\r\n";
    } else if (strcmp(ext, ".3g2") == 0) {
        return "Content-Type: video/3gpp2\r\n\r\n";
    } else if (strcmp(ext, ".7z") == 0) {
        return "Content-Type: application/x-7z-compressed\r\n\r\n";
    } else {
        return "Content-Type: text/plain\r\n\r\n";
    }
}
