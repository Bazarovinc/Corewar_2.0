#!/bin/bash
function sel {

if [[ $1 = 0 ]]
then
echo Asombra.cor
fi

if [[ $1 = 1 ]]
then
echo Kappa.cor
fi

if [[ $1 = 2 ]]
then
echo be.cor
fi

if [[ $1 = 3 ]]
then
echo bee_gees.cor
fi

if [[ $1 = 4 ]]
then
echo doge.cor
fi

if [[ $1 = 5 ]]
then
echo justin_bee.cor
fi

if [[ $1 = 6 ]]
then
echo katchup.cor
fi

if [[ $1 = 7 ]]
then
echo sencha.cor
fi

if [[ $1 = 8 ]]
then
echo tchupka.cor
fi

if [[ $1 = 9 ]]
then
echo terminator.cor
fi

if [[ $1 = 10 ]]
then
echo wasp.cor
fi
}

start=1

if [[ $1 = 1 ]]
then
for ((i = 0; i < 11; i++))
do
T=$(date +%H:%M:%M)
echo "$T"
if [[ $start = 1 ]]
then
i=$2
start=0
fi
echo "i = $i;"
ia=$(sel $i)
./corewar $ia
done
fi

if [[ $1 = 2 ]]
then
for ((i = 0; i < 11; i++))
do
ia=$(sel $i)
for ((j = 0; j < 11; j++))
do
if [ $i = 3 -a $j = 1 ]
then
j=2
fi
ib=$(sel $j)
T=$(date +%H:%M:%M)
echo "$T"
echo "i = $i; j = $j;"
if [ $start = 1 ]
then
i=$2
j=$3
start=0
fi
./corewar $ia $ib
done
done
fi

if [[ $1 = 3 ]]
then
for ((i = 0; i < 11; i++))
do
ia=$(sel $i)
for ((j = 0; j < 11; j++))
do
ib=$(sel $j)
for ((k = 0; k < 11; k++))
do
ic=$(sel $k)
T=$(date +%H:%M:%M)
echo "$T"
echo "i = $i; j = $j; k = $k;"
if [ $start = 1 ]
then
i=$2
j=$3
k=$4
start=0
fi
./corewar $ia $ib $ic
done
done
done
fi

if [[ $1 = 4 ]]
then
for ((i = 0; i < 11; i++))
do
ia=$(sel $i)
for ((j = 0; j < 11; j++))
do
ib=$(sel $j)
for ((k = 0; k < 11; k++))
do
ic=$(sel $k)
for ((t = 0; t < 11; t++))
do
id=$(sel $t)
T=$(date +%H:%M:%M)
echo "$T"
echo "i = $i; j = $j; k = $k; t = $t"
if [ $start = 1 ]
then
i=$2
j=$3
k=$4
d=$5
start=0
fi
./corewar $ia $ib $ic $id
done
done
done
done
fi
