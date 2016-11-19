#!/bin/bash
cppfiles=$(find . -name "*.cpp")
all=$(find . -name "*.h" -o -name "*.cpp")

#for file in ${cppfiles} 
#do
#	echo -n "${file%.cpp}.o "
#done

#echo FILES=${cppfiles}
#echo ALL=${all}

touch Make.tmp
for file in ${cppfiles} 
do
	echo "${file%.cpp}.o : ${file}" >> Make.tmp
	echo "	\${CC} \${CPPFLAGS} ${file} \${OPT} -g -c" >> Make.tmp
done
