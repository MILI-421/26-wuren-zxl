
(cl:in-package :asdf)

(defsystem "tur_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "lir" :depends-on ("_package_lir"))
    (:file "_package_lir" :depends-on ("_package"))
  ))