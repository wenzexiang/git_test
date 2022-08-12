# !/bin/bash


#定义封装线程数的变量
thread=5

tmp_fifofile=/tmp/$$.fifo

#线程开启时，时间
start_time=`date +%s`

#创建命名管道
mkfifo $tmp_fifofile

#将文件描述符(fd)指向管道
exec 6<>$tmp_fifofile

#可以将命名管道删除
rm -rm $tmp_fifofile

#给每一个线程放一个令牌
for i in `seq $thread`
do

	echo >&6

done

# ping 集群中所有的主机ip
for i in {1..200}
do
	#从管道读取令牌
	reap -u 6
	{
		sleep 1
		ip=172.25.88.$i
		ping -c1 -w1 $ip &> /dev/null
		if[ $? -eq 0];then
			echo "$i 是活跃的"
		else
			echo "$i.......服务器宕机"
		fi
			echo >&6
	}&

done

#调用wait方法，判断所有线程
wait

#计算多线程并发，判断所有线程
echo "多线程并发消耗的时间:`expr end_time-start_time`"

#关闭文件描述符fd
exec 6<&- #关闭文件描述符
exec 6<&-








#线程结束是时间
end_time=`date +%s`

