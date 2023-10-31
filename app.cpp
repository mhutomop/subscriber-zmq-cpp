//  Subscribe to the 'Hello'
#include <string>
#include <iostream>
#include <vector>
#include <thread>

#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a PULL socket and connect to interface
    zmq::socket_t pullSocket{context, zmq::socket_type::pull};
    pullSocket.connect("tcp://localhost:5555");

    std::cout << "Subscriber listen!" << std::endl;

    while (true) {
        // Receive all parts of the message
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result =
            zmq::recv_multipart(pullSocket, std::back_inserter(recv_msgs));
        assert(result && "recv failed");
        assert(*result == 1);

        std::cout << "Received: [" << recv_msgs[0].to_string() << "] " << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    return 0;
}
