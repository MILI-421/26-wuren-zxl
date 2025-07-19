; Auto-generated. Do not edit!


(cl:in-package turtle_control_pkg-msg)


;//! \htmlinclude TurtleSpeed.msg.html

(cl:defclass <TurtleSpeed> (roslisp-msg-protocol:ros-message)
  ((linear_speed
    :reader linear_speed
    :initarg :linear_speed
    :type cl:float
    :initform 0.0))
)

(cl:defclass TurtleSpeed (<TurtleSpeed>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TurtleSpeed>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TurtleSpeed)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name turtle_control_pkg-msg:<TurtleSpeed> is deprecated: use turtle_control_pkg-msg:TurtleSpeed instead.")))

(cl:ensure-generic-function 'linear_speed-val :lambda-list '(m))
(cl:defmethod linear_speed-val ((m <TurtleSpeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader turtle_control_pkg-msg:linear_speed-val is deprecated.  Use turtle_control_pkg-msg:linear_speed instead.")
  (linear_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TurtleSpeed>) ostream)
  "Serializes a message object of type '<TurtleSpeed>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linear_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TurtleSpeed>) istream)
  "Deserializes a message object of type '<TurtleSpeed>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear_speed) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TurtleSpeed>)))
  "Returns string type for a message object of type '<TurtleSpeed>"
  "turtle_control_pkg/TurtleSpeed")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TurtleSpeed)))
  "Returns string type for a message object of type 'TurtleSpeed"
  "turtle_control_pkg/TurtleSpeed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TurtleSpeed>)))
  "Returns md5sum for a message object of type '<TurtleSpeed>"
  "b4f9da7bc5185841ef96b23f35977b70")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TurtleSpeed)))
  "Returns md5sum for a message object of type 'TurtleSpeed"
  "b4f9da7bc5185841ef96b23f35977b70")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TurtleSpeed>)))
  "Returns full string definition for message of type '<TurtleSpeed>"
  (cl:format cl:nil "float64 linear_speed  # 定义线速度字段~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TurtleSpeed)))
  "Returns full string definition for message of type 'TurtleSpeed"
  (cl:format cl:nil "float64 linear_speed  # 定义线速度字段~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TurtleSpeed>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TurtleSpeed>))
  "Converts a ROS message object to a list"
  (cl:list 'TurtleSpeed
    (cl:cons ':linear_speed (linear_speed msg))
))
