# UE5 ARPG 战斗框架

**演示视频**：[点击观看](https://www.bilibili.com/video/BV19RDLBtEBt)

## 项目简介

基于 UE5 的 ARPG 核心玩法框架，展示角色分层、战斗系统、物品拾取、敌人 AI、动画驱动等模块。

### 继承体系
- 基类封装受击、死亡、蒙太奇管理，派生类覆写具体行为

### 接口解耦
- `HitInterface`：统一受击响应（角色、敌人、可破坏物）
- `PickupInterface`：角色处理拾取逻辑，物品仅负责碰撞与表现

### 物品与武器
- `Item` → `Soul` / `Treasure` / `Weapon`
- 武器挂载骨骼插槽，碰撞盒 + BoxTrace 攻击判定

### 动画与运动扭曲
- 攻击蒙太奇随机段落 + Motion Warping 实现攻击吸附

### 敌人 AI 状态机
`Patrolling` → `Chasing` → `Attacking` → `Engaged` → `Dead`  
PawnSensing 视线检测，NavMesh 移动，受击打断并可选反击

## 🔧 运行说明

- **引擎**：UE 5.7.3
- **操作**：WASD 移动，空格跳跃，鼠标左键攻击，鼠标右键闪避，E 拾取武器

## 📦 素材声明

所有美术资源均来源于 UE 商城免费资产或公开免费素材，仅用于学习展示，非商业用途。