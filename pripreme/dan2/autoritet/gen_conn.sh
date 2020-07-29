#Usage: bash gen_conn.sh gen_tree seed N M
./$1 $2 $3 > tree
./gen_connected $2 $3 $4 < tree > conn
