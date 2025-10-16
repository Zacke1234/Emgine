#include "Message.h"
#include <stdio.h>
#include <map>
Message::Message() {

}
// 
//
//
////
////
//Message::Message()
//{
//	///*MeshManager::Allocate();+
//	//myMeshManager = &MeshManager::Get();
//	//myObjLoader = new ObjLoader();*/
//	//
//
//	//if (type == MessageType::String)
//	//{
//	//	delete data.msg;
//	//}
//}
// // ??
//void MyBaseManager::setMessage(Message* m)
//{
//	message = m;
//	//std::cout << "ObjLoader loaded mesh in" << "\n";
//}
//
//void MessageQueueComponent1::PerformMessage1()
//{
//	std::cout << "Component 1 peforms Message 1" << "\n";
//	message->Notify(this, "Message 1");
//}
//void MessageQueueComponent1::PerformMessage2()
//{
//	std::cout << "Component 1 perform Message 2" << "\n";
//	message->Notify(this, "Message 2");
//}
//void MessageQueueComponent2::PerformMessage3()
//{
//	std::cout << "Component 2 perform Message 3" << "\n";
//	message->Notify(this, "Message 3");
//} 
//void MessageQueueComponent2::PerformMessage4()
//{
//	std::cout << "Component 2 perform Message 4" << "\n";
//	message->Notify(this, "Message 2");
//}
//
//void ConcreteMessage::Notify(MyBaseManager* sender, std::string event) const 
//{
//	if (event == "Message 1") {
//		std::cout << "Message reacts on Message 1 and triggers following operations: " << "\n";
//		comp2->PerformMessage3();
//	}
//	if (event == "Message 4") {
//		std::cout << "Message reacts on Message 4 and triggers following operations: " << "\n";
//		comp1->PerformMessage2();
//		comp2->PerformMessage3();
//	}
//
//}
//
//void ThreadingMessage::SendMessage()
//{
//
//}
//
//void OBJLoaderMessage::SendMessage()
//{
//
//}
//
////void ConcreteMessage::Notify(MyBaseManager* mb, std::string event)
////{
////	
////}
//
////
////std::string Message::GetStringData()
////{
////	if (type == MessageType::String)
////	{
////		return *data.msg;
////
////	}
////	return std::string();
////}
////
////float Message::GetFloatData()
////{
////	if (type == MessageType::FloatMessage)
////	{
////		return data.FloatMsg;
////	}
////	return 0.0f;
////}
////
////
////Message::MessageType Message::GetMessageType()
////{
////	return type;
////}
////
////Message::Message(std::string msg)
////{
////	
////	type = MessageType::String;
////	data.msg = new std::string(msg);
////	
////
////}
////
////
////Message::MessageData::MessageData()
////{
////	
////} 
////
////
////void MyManager::ProcessMessage(Message* message)
////{
////	const string& msg = message->GetStringData();
////	
////	//printf("", msg);
////	/*switch (message->GetMessageType())
////	{
////	case Message::MessageType::String:
////		if (msg == "ObjLoaderStart") {
////			std::cout << msg << endl;
////		}
////		else if (msg == "ObjLoaderStop")
////		{
////			std::cout << msg << endl;
////		} 
////		break;
////
////		
////		     
////	}*/
////
////	
////}
////
////void MessageQueueClass::QueueMessage(Message* message)
////{
////	messages.push(message);
////}
////
////void MessageQueueClass::ProcessMessages()
////{
////	while (messages.size())
////	{
////		Message* message = messages.front();
////		messages.pop();
////		ProcessMessage(message);
////		delete message;
////	}
////}
////
////void MessageQueueClass::ProcessMessage(Message* message)
////{
////	
////}
////
//
//
//
//
