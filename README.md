# ocpp!mania
..........
Cpp小学期大作业。。。<br>
非诚勿扰<br>
不要吐槽为什么这里是ocpp!mania而repo名是QTCppGame，一开始命名荒你懂吗( • ̀ω•́ )✧

一个cpp版osu!mania
osu官网: [https://osu.ppy.sh](https://osu.ppy.sh/)

# Requirements
- Qt 4.7.0
- 貌似因为Qt太废所以对性能消耗有点高，请使用好一点的GPU

# Building and running

手动修改QTCppGame.pro的最后一行为：<br>
```pro
LIBS += -L {你的项目路径} -l bass
```

然后将assets目录以及bass.dll复制到你最后输出.exe可执行文件的目录下。<br>
你就可以愉快的玩耍了！<br>

如果你是使用的CMakeLists.txt构建的。。。请告诉我怎么设置，我也没找到用CMakeLists.txt输出可以好好运行的版本的方法<br>

自己添加歌曲请放在assets/songs里，并将main.cpp里被注释掉的代码解开，就会自动刷新songs.json文件了（可能会耗一点时间）
