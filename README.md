# DDTools （UE项目开发过程中的一些快捷脚本）


# 目前已有的功能
- 顶部菜单栏
  * SwitchLanguage(编辑器语言在中文和英文之间随时切换)\
  * GoToProject（前往项目GitHub主页）\
  * MountAsset(挂载相关设置)
    * 通过读取Config/MountConfig.txt文件开启自动挂载文件夹。通过启动后的Mount面板添加的挂载也会添加到这里
    * 配置文件书写格式：每行一个路径，最差一定是Content结尾的例如
      * ```F:\TestMount\Content```
    * 其他实例：
      * ```F:\TestMount\Content\Megascans```
- ContentBrowser右键菜单
	* DDTools(材质球相关)
		* FixMaterialSampler16（修复材质球贴图超过16张的报错。将材质球以及引用的MaterialFunction内所有TextureSapler节点的类型更改为Warp）
		* OpenMaterialRayTraceShadow（打开材质球的光追阴影开关；仅半透明材质有效，其他类型材质球将会被忽略）
	* DDTools(StaticMesh相关)
		* 移除所有LOD
		* 自动生成至LOD8
	* DDTools（贴图纹理相关）
		* 开发中
- 其他功能
  * 1、注册自定义UMG工具面板。
    * 在插件Config文件夹下，读取AutoRegisterMenu.txt文件，引擎启动的时候自动注册相关UMG面板。配置文件书写规则如下
      显示名称=UMG路径（可以通过右键UMG，复制引用获得）
	  ```DisplayName=/Script/Blutility.EditorUtilityWidgetBlueprint'/Game/BB.BB'```