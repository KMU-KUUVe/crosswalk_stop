# 2018 lane detector using opencv only

## branches
* master: KASA competition lane detector (continuous lane)
* pams: PAMS competition lane detector (dotted lane)

## About main codes(classes)
* LinePointDetector: 차선 검출을 위해 차선 위의 점을 찾는 클래스
* LaneDetector: LinePointDetector를 이용하여 차선을 검출하는 클래스
* CrosswalkStopNode: LaneDetector를 이용한 ROS 노드 클래스 
* main: CrosswalkStopNode 클래스 객체를 생성하여 노드를 생성하는 메인 함수 
* *Dependency: etc/Class Diagram.png 참고*

## About launch files





## Debug mode printlog parsing
If you want to use this code outside(on the real road), erase the code on the part that written '//indoor test'.
