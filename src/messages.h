// Sends and receives data through the messages port.
//
// The data transfer protocol:
// - Each request consists from 2 bytes.
// - The first byte is the request type.
// - The second byte is the data of request.
#pragma once

#include <cstring>
#include <zmq.hpp>
#include "env.h"

namespace synth::messages {

enum Message {
	kRemoveNote = 0,
	kAddNote    = 1,
};

void Receive(zmq::socket_t& socket, Environment& env);

zmq::socket_t& CreateSocket();

inline void Send(
		Message message, char data, zmq::socket_t& socket = CreateSocket()) {
	const char buffer[] = {char(message), data};
	zmq::message_t reply(2);
	std::memcpy(reply.data(), buffer, 2);
	socket.send(reply);
}

inline void Send(const char* data) {
	Send(Message(data[0]), data[1]);
}

} // namespace synth::messages
