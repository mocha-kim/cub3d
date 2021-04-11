gcc -Wall -Werror -Wextra gnl/*.c config/*.c utils/*.c main.c -o parse_map;
./parse_map ./maps/test.cub
./parse_map ./maps/fail.cub