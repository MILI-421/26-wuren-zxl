;; Auto-generated. Do not edit!


(when (boundp 'tur_msgs::lir)
  (if (not (find-package "TUR_MSGS"))
    (make-package "TUR_MSGS"))
  (shadow 'lir (find-package "TUR_MSGS")))
(unless (find-package "TUR_MSGS::LIR")
  (make-package "TUR_MSGS::LIR"))

(in-package "ROS")
;;//! \htmlinclude lir.msg.html


(defclass tur_msgs::lir
  :super ros::object
  :slots (_turtle_linear ))

(defmethod tur_msgs::lir
  (:init
   (&key
    ((:turtle_linear __turtle_linear) 0.0)
    )
   (send-super :init)
   (setq _turtle_linear (float __turtle_linear))
   self)
  (:turtle_linear
   (&optional __turtle_linear)
   (if __turtle_linear (setq _turtle_linear __turtle_linear)) _turtle_linear)
  (:serialization-length
   ()
   (+
    ;; float32 _turtle_linear
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _turtle_linear
       (sys::poke _turtle_linear (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _turtle_linear
     (setq _turtle_linear (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get tur_msgs::lir :md5sum-) "b17f578a1d094a85f0845837e7f90e5c")
(setf (get tur_msgs::lir :datatype-) "tur_msgs/lir")
(setf (get tur_msgs::lir :definition-)
      "float32 turtle_linear #定义一个变量，用于存储线速度

")



(provide :tur_msgs/lir "b17f578a1d094a85f0845837e7f90e5c")


