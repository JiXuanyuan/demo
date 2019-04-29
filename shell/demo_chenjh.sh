#!/bin/sh

ARG_HELP='
###########################################################################
#
#	Shell Demo
#	@ 陈佳辉 2019/03/27创建
#	版本：20190430 v1.02
#	功能：
#		循环打印指定文本内容，并可保存log。
#		该脚本为演示Shell功能，尽量采用多种语法格式。
#	参数：
#		-h	显示该帮助文本
#		-l	log保存路径
#		-e	是否显式显示log
#		-t	循环次数
#		-c	文本内容
#		-s	执行脚本
#	示例：'$0' -t 5 -c "This is a demo."
#
###########################################################################
'

ARG_LOG="$(dirname $0)/tmp.log"
ARG_ECHO=true
ARG_TIMES=1
ARG_CONTENT=""
ARG_SCRIPT=""

# 解析选项参数值，并映射功能函数
this_map_arg_func() {
	arg=$1
	func=$2
	value=""
	shift 2
	#解析参数值
	while [ ! "$1" = "" ]; do
		if [ "$1" = "$arg" ]; then
			#参数值不为空或“-”开头，则保存参数值
			[ "$2" = "" ] || (echo "$2" | grep -n "^-" >/dev/null) \
				|| value=$2
			#映射函数与参数值
			$func $value
			return 0
		fi
		shift
	done
	return 1
}

# 解析选项多个参数值，或字符串，并映射功能函数
this_map_str_func() {
	arg=$1
	func=$2
	value=""
	shift 2
	#解析参数值
	while [ ! "$1" = "" ]; do
		[ ! "$1" = "$arg" ] && shift && continue
		#如果参数值引号开头，则值到引号结束
		if (echo "$2" | grep -n "^\"" >/dev/null); then
			shift
			for var in $@; do
				value="$value $var"
				#如果参数值引号结尾，则退出循环
				(echo "$var" | grep -n "\"$" >/dev/null) && break
			done
		else
			#参数值不为空和“-”开头，则保存参数值
			while [ ! "$2" = "" ] && \
					! (echo "$2" | grep -n "^-" >/dev/null); do
				value="$value $2"
				shift
			done
		fi
		#映射函数与参数值
		$func $value
		return 0
	done
	return 1
}

this_print() {
	TAG="#"
	#显示信息
	$ARG_ECHO && echo $TAG $@
	#保存LOG
	[ -f "$ARG_LOG" ] && echo $TAG $@ >> $ARG_LOG
	return 0
}

func_log() {
	[ ! -f "$1" ] && touch $1
	[ ! -f "$1" ] && this_print "-l 参数错误: $1" && return 1

	ARG_LOG=$1
	this_print "保存路径: $ARG_LOG"
	return 0
}

func_echo() {
	[ ! "$1" = "true" ] && [ ! "$1" = "false" ] \
		&& this_print "-e 参数错误: $1" && return 1
	
	ARG_ECHO=$1
	return 0
}

func_times() {
	!(echo "$1" | grep -w -n "[1-9][0-9]*" >/dev/null) \
		&& this_print "-t 参数错误: $1" && return 1
	
	ARG_TIMES=$1 
	return 0
}

func_content() {
	ARG_CONTENT=$*
	return 0
}

func_script() {
	#去掉引号，不止去掉两端引号，可能有问题20190430
	ARG_SCRIPT=$(echo $@ | sed 's/\"//g')
	return 0
}

func_help() {
	echo "$ARG_HELP"
	exit 0
}


main() {
	#创建log文件
	echo " Shell Demo " >> $ARG_LOG

	this_print "$ARG_LOG, $ARG_TIMES, \"$ARG_CONTENT\", $ARG_SCRIPT"
	this_print "$(date) 开始测试===>"

	while (( i < $ARG_TIMES )); do
		i=$((i + 1))
		this_print "当前次数: $i"
		this_print "$ARG_CONTENT"
		this_print $($ARG_SCRIPT)
	done

	this_print "$(date) <===测试结束"
	return 0
}

this_map_arg_func -h func_help $@

this_map_arg_func -l func_log $@
this_map_arg_func -e func_echo $@
this_map_arg_func -t func_times $@
this_map_str_func -c func_content $@
this_map_str_func -s func_script $@

main

exit 0

