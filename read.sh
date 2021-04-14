gcc -Wall -Werror -Wextra gnl/*.c config/*.c utils/*.c main.c -o parse_map;
./parse_map ./maps/test.cub

echo "fail case"
for ((i=1;i<=57;i++))
do
	echo $i
	./parse_map ./maps/fail$i.cub
done

echo "success"
for ((i=1;i<=12;i++))
do
	echo $i
	./parse_map ./maps/test$i.cub
done