// Auto-generated. Do not edit!

// (in-package tur_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class lir {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.turtle_linear = null;
    }
    else {
      if (initObj.hasOwnProperty('turtle_linear')) {
        this.turtle_linear = initObj.turtle_linear
      }
      else {
        this.turtle_linear = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lir
    // Serialize message field [turtle_linear]
    bufferOffset = _serializer.float32(obj.turtle_linear, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lir
    let len;
    let data = new lir(null);
    // Deserialize message field [turtle_linear]
    data.turtle_linear = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'tur_msgs/lir';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b17f578a1d094a85f0845837e7f90e5c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 turtle_linear #定义一个变量，用于存储线速度
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lir(null);
    if (msg.turtle_linear !== undefined) {
      resolved.turtle_linear = msg.turtle_linear;
    }
    else {
      resolved.turtle_linear = 0.0
    }

    return resolved;
    }
};

module.exports = lir;
