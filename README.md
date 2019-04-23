# demo
# 测试git命令

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
        比较工作区与暂存区
            git diff
        执行add后，比较暂存区与本地版本库
            git diff --cached HEAD
        执行commit后，比较远端代码库与本地版本库
            git diff origin/master HEAD
        （使用git reset，可撤销add操作）
    4）修改并提交代码
        git add test.c
        git commit -m "add test.c" （添加-a，commit所有修改）
        git push
    
  
