
20220712更：新增撤销前一次编辑痕迹功能，通过设置“点击行为”栈，来进行控制

（鉴于最近有出现一些下载后的问题，备注下，1，是可能会有构建目录和文件目录不同级，这个可以在qt的“项目”设置构建目录到工程文件根目录Screenshot-with-picture-edit即可，另外就是在res.qrc文件中，删除掉了一个无效的图片链接。下载后亲测可用。谢谢，咨询wx：lidian1993）
基于Qt的截图工具，采用了类似QQ截图的控制面板，实现截图后直接进行编辑
截图的思路主要是先得到当前的全屏图，然后沿着这个全屏图绘制一大圈路径，然后用暗色填充，即得到了背景大图。基本的截图操作就是根据鼠标初始按下的位置和最终松开的位置，根据这两个位置点，得到一个矩形，按照这个矩形绘制路径，然后再从背景大路径中将这个小路径用subpath扣掉，想要得到的截图区域就出现了。截图后的编辑功能是采用了将截取区域的图绘制到一个额外引入的label上面，利用编辑区按钮触发后在其中进行编辑操作。定义想要编辑的图形种类的结构体，引入QVector向量进行保存。 
马赛克及撤销功能有待添加，，

基本截图：
![基本截图](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima1.jpg)

文字编辑：
![文字编辑](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima.jpg)

画箭头：
![画箭头](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima2.jpg)

画矩形：
![画矩形](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima3.jpg)

画圆形：
![画圆形](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima4.jpg)

同时编辑：
![同时编辑](https://github.com/lidian53/Screenshot-with-picture-edit-Based-on-Qt/blob/master/screenimage/ima5.jpg)
