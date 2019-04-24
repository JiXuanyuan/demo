# demo
## git命令

    1）创建项目init
        git init
    2）导入项目clone
        git clone https://github.com/JiXuanyuan/demo.git
        （默认创建，origin远端代码库的标签，master主分支标签）
    3）比较差异diff
        区概念：
            工作区（本地代码）<—add—>暂存区（--cached）
            <—commit—>本地版本库（HEAD，默认master）
            <—push—>远端代码库（默认origin/master）
        命令：
        比较暂存区与工作区
            git diff
        执行add后，比较本地版本库与暂存区
            git diff HEAD --cached
        执行commit后，比较远端代码库与本地版本库
            git diff origin/master HEAD
    4）修改并提交代码
        git add test.c  （使用git reset，可撤销add操作）
        git commit -m "add test.c" （添加-a，commit所有修改）
        git push    （使用git push -u origin master ，指定master分支）
    5）检出文件
        git checkout -- newfile （删除本地文件后，可再检出newfile文件
    6）更新代码
        git fetch
        git merge
        使用pull，commitID不变，多数时候相当于fetch + merge
            git pull
    7）查看、创建、切换分支
        git branch -a
        git branch day1
        git checkout day1
        git checkout 406ac5a （切换到短哈希为406ac5a的时间点）
    8）合并分支  
        git merge day1  （将day1分支合并到当前分支）
        git commit -m "This is a merge." 
        git push
    9）删除分支
        git branch -d day2
        git push origin --delete day2   （删除远程分支） 
    10）显示状态status
        git status
    11）显示日志log
        git log
        git log --oneline --graph
        git log --pretty=format:"%h %an, %ad : %s" --date=iso
        （使用git config log.date iso，本地配置时间格式）
        git log -p -3  （-p显示提交的内容差异，-3显示最近3次更新）
    12）建立远程库
        git remote add origin https://github.com/JiXuanyuan/demo.git
        git remote -v   （显示远程库）
    13）Pull Requests 
        在github上，将次分支merge到master分支（或用命令git request-pull）
    
  
