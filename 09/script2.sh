#! /bin/sh

BOOK = $HOME/phonebook.data
echo find what name in phonebook
read NAME
if grep $NAME $BOOK > /tmp/pb.tmp
then
	echo Entries for $NAME
	cat /tmp/pb.tmp
else
	echo No entries for $NAME
fi

rm /tmp/pb.tmp

