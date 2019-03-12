#include "messages.h"
#include "env.h"
// #include "store.h"

namespace synth::messages {

namespace {

zmq::context_t context(1);
zmq::socket_t* socket;

} /* namespace */

zmq::socket_t& CreateSocket() {
	if (socket == nullptr) {
		socket = new zmq::socket_t(context, ZMQ_REP);
		socket->bind("tcp://127.0.0.1:1234");
	}
	return *socket;
}

void Receive(zmq::socket_t& socket, Environment& env) {
	// zmq::message_t reply;
	// socket.recv(&reply);
	// auto data = static_cast<const char*>(reply.data());
	//
	// switch (Message(data[0])) {
	// 	case kRemoveNote:
	// 		env.RemoveNoteWithOctave(data[1]);
	// 		break;
	// 	case kAddNote:
	// 		env.AddNoteWithOctave(data[1]);
	// 		break;
	// }
}

} // namespace synth::messages
