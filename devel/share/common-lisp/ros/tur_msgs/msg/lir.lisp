; Auto-generated. Do not edit!


(cl:in-package tur_msgs-msg)


;//! \htmlinclude lir.msg.html

(cl:defclass <lir> (roslisp-msg-protocol:ros-message)
  ((turtle_linear
    :reader turtle_linear
    :initarg :turtle_linear
    :type cl:float
    :initform 0.0))
)

(cl:defclass lir (<lir>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lir>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lir)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name tur_msgs-msg:<lir> is deprecated: use tur_msgs-msg:lir instead.")))

(cl:ensure-generic-function 'turtle_linear-val :lambda-list '(m))
(cl:defmethod turtle_linear-val ((m <lir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tur_msgs-msg:turtle_linear-val is deprecated.  Use tur_msgs-msg:turtle_linear instead.")
  (turtle_linear m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lir>) ostream)
  "Serializes a message object of type '<lir>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'turtle_linear))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lir>) istream)
  "Deserializes a message object of type '<lir>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'turtle_linear) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lir>)))
  "Returns string type for a message object of type '<lir>"
  "tur_msgs/lir")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lir)))
  "Returns string type for a message object of type 'lir"
  "tur_msgs/lir")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lir>)))
  "Returns md5sum for a message object of type '<lir>"
  "b17f578a1d094a85f0845837e7f90e5c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lir)))
  "Returns md5sum for a message object of type 'lir"
  "b17f578a1d094a85f0845837e7f90e5c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lir>)))
  "Returns full string definition for message of type '<lir>"
  (cl:format cl:nil "float32 turtle_linear #定义一个变量，用于存储线速度~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lir)))
  "Returns full string definition for message of type 'lir"
  (cl:format cl:nil "float32 turtle_linear #定义一个变量，用于存储线速度~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lir>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lir>))
  "Converts a ROS message object to a list"
  (cl:list 'lir
    (cl:cons ':turtle_linear (turtle_linear msg))
))
