#!/bin/sh

ARG_HELP='
###########################################################################
#
#   Shell Demo
#   @ 陈佳辉 2019/03/27
#   功能：实现循环打印指定文本内容，并可保存log。
#       该脚本为演示Shell功能，尽量采用多种语法格式
#   参数：
#       -h  显示该帮助文本
#       -l  log保存路径
#       -e  是否显式显示log
#       -t  循环次数
#       -c  文本内容
#
###########################################################################
'

ARG_LOG="./tmp.log"
ARG_ECHO=true
ARG_TIMES=5
ARG_CONTENT="Hello World!"

# 解析选项参数值，并映射功能函数
this_map_arg_func() {
	ARG=$1
	FUNC=$2
	ARG_VALUE=""
	shift 2
	#解析参数值
	while [ ! "$1" = "" ]; do
		if [ "$1" = "$ARG" ]; then
			#参数值不为空或“-”开头，则保存参数值
			[ "$2" = "" ] || (echo "$2" | grep -n "^-" >/dev/null) \
				|| ARG_VALUE=$2
			#映射函数与参数值
			$FUNC $ARG_VALUE
			return 0
		fi
		shift
	done
	return 1
}

# 解析选项多个参数值，或字符串，并映射功能函数
this_map_str_func() {
	ARG=$1
	FUNC=$2
	ARG_VALUE=""
	shift 2
	#解析参数值
	while [ ! "$1" = "" ]; do
		[ ! "$1" = "$ARG" ] && shift && continue
		#参数值不为空和“-”开头，则保存参数值
		while [ ! "$2" = "" ] && ! (echo "$2" | grep -n "^-" >/dev/null); do
			ARG_VALUE="$ARG_VALUE $2"
			shift	
		done
		#映射函数与参数值
		$FUNC $ARG_VALUE
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
	[ ! -f "$1" ] && this_print "-e 参数错误: $1" && return 1

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

func_help() {
	echo "$ARG_HELP"
	exit 0
}

main() {
	#创建log文件
	echo " Shell Demo " >> $ARG_LOG
	this_print "$ARG_LOG, $ARG_ECHO, $ARG_TIMES, \"$ARG_CONTENT\""
	this_print "$(date) 开始测试===>"

	while (( i < $ARG_TIMES )); do
		i=$((i + 1))
		this_print "当前次数: $i"
		this_print "$ARG_CONTENT"
	done

	this_print "$(date) <===测试结束"
	return 0
}

this_map_arg_func -h func_help $@

this_map_arg_func -l func_log $@
this_map_arg_func -e func_echo $@
this_map_arg_func -t func_times $@
this_map_str_func -c func_content $@

main

exit 0

