DTCC=../build/dtcc2tests

for i in *.c
do
	$DTCC $i
done
