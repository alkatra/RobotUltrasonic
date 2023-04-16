import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class ScaredRobot(Node):


    def listener_callback(self, msg):
        clean = msg.data[1:] #removes the [                                       
        clean2 = clean[:-2] #removes the ]\n                                  
        readings = clean2.split(',')

        try:
            left = int((readings[0])[:-2])
            front = int((readings[1])[:-2])
            right = int((readings[2])[:-2])
            self.left_last = left
            self.front_last = front
            self.right_last = right
        except:
            left = left_last
            front = front_last
            right = right_last


        if(front < 5):
            if(left > right):
                self.backward(180)
            else:
                self.backward(180)
            
        
        elif((front < 30) and (left > right)):
            self.leftward(300)
        
        elif((front < 30) and (right > left)):
            self.rightward(300)


        elif(left < 30):
            self.rightward(100)
        
        elif (right < 30):
            self.leftward(100)




        
        else:
            self.forward(120)
        



    def forward (self, delay):
        msg = String()
        msg.data = "MOVEF:0"+str(delay)+"\n"
        self.publisher.publish(msg)
    

    def backward (self, delay):
        msg = String()
        msg.data = "MOVEB:0"+str(delay)+"\n"
        self.publisher.publish(msg)
    

    def leftward(self, delay):
        msg = String()
        msg.data = "TURNL:0"+str(delay)+"\n"
        self.publisher.publish(msg)
    

    def rightward(self, delay):
        msg = String()
        msg.data = "TURNR:0"+str(delay)+"\n"
        self.publisher.publish(msg)

    def backpivot(self, delay):
        msg = String()
        msg.data = "BACKP:0"+str(delay)+"\n"
        self.publisher.publish(msg)

    def __init__(self):
        super().__init__('ScaredRobot')
        self.publisher = self.create_publisher(String, '/robot/control', 10)

        self.subscription = self.create_subscription(
            String,
            '/robot/all',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

def main(args=None):
    rclpy.init(args=args)

    scaredrobot = ScaredRobot()
    rclpy.spin(scaredrobot)
    
    scaredrobot.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
