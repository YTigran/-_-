#!/bin/bash

# Ֆունկցիա՝ Էկրանին տպել սարքի IPv4 և IPv6 հասցեները
function print_ip_addresses() {
    echo "IPv4 հասցեները:"
    ip -4 addr show | grep inet | awk '{print $2}'
    echo "IPv6 հասցեները:"
    ip -6 addr show | grep inet6 | awk '{print $2}'
}

# Ֆունկցիա՝ traceroute միջոցով ցանցային ճանապարհը ցույց տալ
function trace_route() {
    read -p "Մուտքագրեք հանգույցի անունը (hostname կամ URL): " host
    echo "Ցանցային ճանապարհը դեպի $host:"
    traceroute "$host"
}

# Ֆունկցիա՝ IP հասցե ստանալ hostname-ից
function resolve_ip() {
    read -p "Մուտքագրեք հանգույցի անունը (hostname կամ URL): " host
    echo "IP հասցեն $host-ի համար՝"
    getent ahosts "$host" | awk '{print $1}' | head -n 1
}

# Ֆունկցիա՝ տեքստ կամ ֆայլ գաղտնագրել
function encrypt_text_or_file() {
    read -p "Մուտքագրեք գաղտնագրման համար գաղտնաբառը: " password
    read -p "Գաղտնագրել տեքստ (1) թե ֆայլ (2)? " choice
    if [ "$choice" == "1" ]; then
        read -p "Մուտքագրեք տեքստը՝ " text
        echo "$text" | openssl enc -aes-256-cbc -e -base64 -pass pass:"$password"
    elif [ "$choice" == "2" ]; then
        read -p "Մուտքագրեք ֆայլի անունը՝ " filename
        openssl enc -aes-256-cbc -e -base64 -in "$filename" -out "${filename}.enc" -pass pass:"$password"
        echo "Գաղտնագրված ֆայլը՝ ${filename}.enc"
    fi
}

# Ֆունկցիա՝ տեքստ կամ ֆայլ վերծանել
function decrypt_text_or_file() {
    read -p "Մուտքագրեք վերծանման համար գաղտնաբառը: " password
    read -p "Վերծանել տեքստ (1) թե ֆայլ (2)? " choice
    if [ "$choice" == "1" ]; then
        read -p "Մուտքագրեք գաղտնագրված տեքստը՝ " text
        echo "$text" | openssl enc -aes-256-cbc -d -base64 -pass pass:"$password"
    elif [ "$choice" == "2" ]; then
        read -p "Մուտքագրեք ֆայլի անունը՝ " filename
        openssl enc -aes-256-cbc -d -base64 -in "$filename" -out "${filename%.enc}" -pass pass:"$password"
        echo "Վերծանված ֆայլը՝ ${filename%.enc}"
    fi
}

# Ֆունկցիա՝ սեղմել ֆայլը
function compress_file() {
    read -p "Մուտքագրեք ֆայլի անունը՝ " filename
    gzip "$filename"
    echo "Սեղմված ֆայլը՝ ${filename}.gz"
}

# Ֆունկցիա՝ վերականգնել սեղմված ֆայլը
function decompress_file() {
    read -p "Մուտքագրեք սեղմված ֆայլի անունը (gzip ձևաչափով՝ *.gz)՝ " filename
    gunzip "$filename"
    echo "Վերականգնված ֆայլը՝ ${filename%.gz}"
}

# Ֆունկցիա՝ ֆայլի արժեքը հաշվել (checksum)
function file_checksum() {
    read -p "Մուտքագրեք ֆայլի անունը՝ " filename
    echo "MD5 checksum:"
    md5sum "$filename"
    echo "SHA256 checksum:"
    sha256sum "$filename"
}

# Գլխավոր մենյու
while true; do
    echo "=== Bash Գործողությունների Մենյու ==="
    echo "1. Էկրանին տպել սարքի IPv4 և IPv6 հասցեները"
    echo "2. Ցույց տալ ցանցային ճանապարհը (traceroute)"
    echo "3. Ստանալ IP հասցե hostname-ից"
    echo "4. Գաղտնագրել ֆայլ/տեքստ"
    echo "5. Վերծանել ֆայլ/տեքստ"
    echo "6. Սեղմել ֆայլը"
    echo "7. Վերականգնել սեղմված ֆայլը"
    echo "8. Հաշվել ֆայլի արժեքը (checksum)"
    echo "9. Ելք"
    read -p "Ընտրեք գործողություն (1-9): " option

    case $option in
        1) print_ip_addresses ;;
        2) trace_route ;;
        3) resolve_ip ;;
        4) encrypt_text_or_file ;;
        5) decrypt_text_or_file ;;
        6) compress_file ;;
        7) decompress_file ;;
        8) file_checksum ;;
        9) echo "Ելք..." ; exit ;;
        *) echo "Սխալ ընտրություն, կրկին փորձեք." ;;
    esac
    echo ""
done

