#include <message_transport/list_transport.h>
#include <cm_transport/Packet.h>

using namespace message_transport;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "list_transport_cm");  
    // LIST_TRANSPORT("cm_transport", cm_transport::CustomMsg)
    LIST_TRANSPORT("cm_transport", cm_transport::Packet)
    
    // {
    // //     printf("\n\n=========== buffer::CustomMsg ===========\n");
    //     ListTransport<cm_transport::CustomMsg> l_cm_transport;
    //     l_cm_transport.run("cm_transport", "cm_transport::CustomMsg");
    // }

	return 0;
}
