gcc -Wall -Werror -Wextra gnl/*.c config/*.c utils/*.c main.c -o parse_map;
./parse_map ./maps/test.cub
# ./parse_map ./maps/fail.cub
# ./parse_map ./maps/fail2.cub
echo "fail case"

for ((i=0;i<=48;i++))
do
	echo $i
	./parse_map ./maps/fail$i.cub
done