;; Auto-generated. Do not edit!


(when (boundp 'turtle_control_pkg::TurtleSpeed)
  (if (not (find-package "TURTLE_CONTROL_PKG"))
    (make-package "TURTLE_CONTROL_PKG"))
  (shadow 'TurtleSpeed (find-package "TURTLE_CONTROL_PKG")))
(unless (find-package "TURTLE_CONTROL_PKG::TURTLESPEED")
  (make-package "TURTLE_CONTROL_PKG::TURTLESPEED"))

(in-package "ROS")
;;//! \htmlinclude TurtleSpeed.msg.html


(defclass turtle_control_pkg::TurtleSpeed
  :super ros::object
  :slots (_linear_speed ))

(defmethod turtle_control_pkg::TurtleSpeed
  (:init
   (&key
    ((:linear_speed __linear_speed) 0.0)
    )
   (send-super :init)
   (setq _linear_speed (float __linear_speed))
   self)
  (:linear_speed
   (&optional __linear_speed)
   (if __linear_speed (setq _linear_speed __linear_speed)) _linear_speed)
  (:serialization-length
   ()
   (+
    ;; float64 _linear_speed
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _linear_speed
       (sys::poke _linear_speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _linear_speed
     (setq _linear_speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get turtle_control_pkg::TurtleSpeed :md5sum-) "b4f9da7bc5185841ef96b23f35977b70")
(setf (get turtle_control_pkg::TurtleSpeed :datatype-) "turtle_control_pkg/TurtleSpeed")
(setf (get turtle_control_pkg::TurtleSpeed :definition-)
      "float64 linear_speed  # 定义线速度字段


")



(provide :turtle_control_pkg/TurtleSpeed "b4f9da7bc5185841ef96b23f35977b70")


