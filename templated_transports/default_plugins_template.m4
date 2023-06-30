
dnl DECLARE_ALL_TEMPLATES(PLUGIN_NAMESPACE,SUFFIX,TYPE) 
define(`DECLARE_ALL_TEMPLATES', `
    <class name="$1/raw_$2_pub" 
		type="message_transport::RawPublisher<$3>" 
		base_class_type="message_transport::PublisherPlugin<$3>">
    <description>
      This is the default publisher. It publishes the objects as-is on the base topic.
    </description>
  </class>

  <class name="$1/raw_$2_sub" 
		type="message_transport::RawSubscriber<$3>" 
		base_class_type="message_transport::SubscriberPlugin<$3>">
    <description>
      This is the default pass-through subscriber for topics of type $3
    </description>
  </class>

  <class name="$1/bz2_$2_pub" 
		type="bz2_transport::BZ2Publisher<$3>" 
		base_class_type="message_transport::PublisherPlugin<$3>">
    <description>
        This publisher publishes its type as BZ2 compressed binary
        blobs
    </description>
  </class>

  <class name="$1/bz2_$2_sub" 
		type="bz2_transport::BZ2Subscriber<$3>" 
		base_class_type="message_transport::SubscriberPlugin<$3>">
    <description>
        This subscriber subscribes to BZ2 binary blobs
    </description>
  </class>
')

