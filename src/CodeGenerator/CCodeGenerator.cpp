#include "CodeGenerator/CCodeGenerator.hpp"
#define INCLUDE_HEADER "#include <stdio.h>\n#include <thread>\n#include <uinstd.h>\n#include <stdlib.h>\n"
#define SIM_INCLUDE ""
#define REAL_INCLUDE "#include \"../../CommLib/NetComm/include/EtherReceiver.hpp\"\n\
#include \"../../CommLib/NetComm/include/EtherSender.hpp\"\n\
#include \"../../CommLib/NetComm/include/UDPSender.hpp\"\n\
#include \"../../CommLib/NetComm/include/UDPReceiver.hpp\"\n"
#define CRYPTO_INCLUDE "#include \"../../CryptoLib/include/Cryptor.hpp\""
#define CR "\n"
#define TAB "\t"
namespace isadt{
    void CCodeGenerator::addPlugin(Plugin* plugin){
        // 1. check the language is the same as the class
		// 2. avoid redundant addition
		for (Plugin* p : this->plugins)
		{
			if (!(!p->getPluginAlgorithmId().compare(plugin->getPluginAlgorithmId())
				|| !p->getPluginLanguage().compare(plugin->getPluginLanguage()))
				|| !p->getPluginName().compare(plugin->getPluginName()))
			{
				std::cout << "Error: plugin adding error, plugin already exists." << std::endl;
			}
			else
			{
				this->plugins.push_front(plugin);
			}
		}
    }

        Plugin*  CCodeGenerator::getFirstPlugin()
        {
            // iterate the list and return the first usable plugin
		    // otherwise return null
		    if (this->plugins.size() > 0)
		    {
		    	return this->getPlugins().front();
		    }
		    else
		    {
		    	std::cout << "WARNING: no available plugin.";
		    	return nullptr;
		    }
        }
        Plugin*  CCodeGenerator::getPlugin(std::string algorithmId, std::string pluginLanguage)
        {
            // get the correspoding plugin in the list
		    // otherwise return null
		    for (Plugin* p : this->getPlugins())
		    {
		    	if (!p->getPluginLanguage().compare(pluginLanguage) &&
		    		!p->getPluginAlgorithmId().compare(algorithmId))
		    	{
		    		return p;
		    	}
		    }
		    std::cout << "WARNING: plugin not found.";
		    return nullptr;
        }  

        void  CCodeGenerator::rmPlugin(std::string pluginName)
        {
            // remove all algorithms of the same plugin
		    for (Plugin* p : this->getPlugins())
		    {
		    	if (!p->getPluginName().compare(pluginName))
		    	{
		    		this->getPlugins().remove(p);
		    	}
		    }
        }

        std::list<Plugin*>  CCodeGenerator::getPlugins()
        {
            return this->plugins;
        }
        // methods for generating header file 
        void  CCodeGenerator::generateHeaderFile(std::string path, Process* proc)
        {
            std::ofstream outHeadFile;
		    //TODO: make sure here
		    std::string tempFileName = proc->getName() + ".h";
		    std::string outStr = "";
		    // if def
		    outStr += generateHeaderIfDef(proc);
		    // generate includes 
		    outStr += this->generateCommonIncludes();
		    outStr += this->generateCommunicationIncludes();
		    outStr += this->generateDependIncludes(proc);
		    // generate attrs and methods declaration
		    // attrs
			outStr += this->generateClassPre(proc);
		    for (Attribute* attr : proc->getAttributes()) {
		    	outStr += "\t\t" + this->appendAttrDef(outStr, attr);
		    }
			outStr += "\tpublic: \n";
		    // methods
		    for (Method* m : proc->getMethods()) {
		    	outStr += "\t\t" + this->appendMethodDeclaration(outStr, m);
		    }
			outStr += "};\n";

		    //endif
		    outStr += "#endif\n";
			std::cout << outStr << std::endl;
		    outHeadFile.open(path + "/generatedHeader" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outHeadFile << outStr << std::endl;
		    outHeadFile.close();
        }

		std::string CCodeGenerator::generateClassPre(Process* proc){
			std::string result = "class " + proc->getName() + " {" + CR;
			result += "\tprivate: \n";
			return result;
		}

        std::string  CCodeGenerator::generateCommonIncludes()
        {
            std::string commonIncludes =
			"#include <iostream>\n#include <string>\n#include <vector>\n#include <stdlib.h>\n#include <uinstd.h>\n";
		    commonIncludes += INCLUDE_HEADER;
		    return commonIncludes;
        }

        std::string  CCodeGenerator::generateCommunicationIncludes()
        {
			// for real world we use libcap or libnet for the ethernet comm
			// use linux socket for the udp transmission
            std::string communicationIncludes = SIM_INCLUDE;
			communicationIncludes += REAL_INCLUDE;
		    return communicationIncludes;
        }

		std::string CCodeGenerator::generateCryptoIncludes()
		{
			std::string cryptoIncludes = CRYPTO_INCLUDE;
			return cryptoIncludes;
		}

        std::string  CCodeGenerator::generateDependIncludes(Process* currentProc)
        {
            //TODO: make sure here
            std::string dependHeaders = CR;
            /*
		    std::string dependHeaders = CR;
		    for (Process* p : currentProc->getDependProcs()) {
		    	//TODO: add path for process here
		    	std::string headerPath;
		    	dependHeaders += "#include \"" + headerPath + "\\" + p->getName() + ".h\" \n";
		    }
            */
            dependHeaders += "#include \"../include/UserType.h\" \n";
		    return dependHeaders;
        }

        std::string  CCodeGenerator::appendAttrDef(std::string inStr, Attribute* attr)
        {
            std::string result = "";
		    result += attr->getType()->getName() + " " + attr->getIdentifier() + ";\n";
		    return result;
        }

        std::string CCodeGenerator::appendMethodDeclaration(std::string inStr, Method* method)
        {
            std::string result = "";
		    std::string attrStr;
		    int i = 1;
		    for (Attribute* a : method->getAttributes()) 
			{
		    	attrStr += a->getType()->getName() + " " + a->getIdentifier();
		    	if (i < method->getAttributes().size()) 
				{
		    		attrStr += ", ";
		    	}
		    	i++;
		    }
		    result += method->getReturnType()->getName() + " " + method->getName() + "(" + attrStr + ");\n";
		    return result;
        }

        std::string CCodeGenerator::generateHeaderIfDef(Process* proc)
        {
            std::string result = "#ifndef " + proc->getName() + "_" + "h" + CR;
		    result += "#define " + proc->getName() + "_" + "h" + CR;
            return result;
        }

        // methods for generating src file
        void  CCodeGenerator::generateSrcFile(std::string path, Process* proc)
        {
            //TODO: imple later
            std::string outStr = "";
		    std::ofstream outSrcFile;
		    std::string tempFileName = proc->getName() + ".cpp";
			std::cout << "genSrcInclude" << std::endl;
		    outStr += this->generateSrcIncludes(proc);
			std::cout << "genSrcInclude Over" << std::endl;
			std::cout << "generateStateDef" << std::endl;
			outStr += this->generateStateDef(proc);
			std::cout << "generateStateDefOver" << std::endl;
			std::cout << "genSrcMethod" << std::endl;
		    outStr += this->generateSrcMethods(proc);
			
			std::cout << "genSrcMethodOver" << std::endl;
			std::cout << "genSrcMain" << std::endl;
		    outStr += this->generateMain(proc);
			
			std::cout << "genSrcMainOver" << std::endl;
			std::cout << outStr << std::endl;
		    outSrcFile.open(path + "/generatedSrc" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outSrcFile << outStr << std::endl;
		    outSrcFile.close();
        }

        std::string  CCodeGenerator::generateStateDef(Process* proc)
        {
            std::string defs = "";
		    //defs += "#define STATE__START__STATE 0\n";
		    int i = 0;
			int loop_count = 0;
			for(StateMachine* sm : proc->getStateMachines()){
				for (Vertex* v : sm->getVertices()) 
				{
		    		//TODO: refine the state definition later
		    		defs += "#define STATE__" + v->getName() + " " + std::to_string(i) + "\n";
		    		i++;
		   	 	}
				loop_count++;
			}
		    
		    //defs += "#define STATE__STOP__STATE " + std::to_string(i) + "\n";
		    return defs;
        }
        
		std::string  CCodeGenerator::generateSrcIncludes(Process* proc)
		{
			//TODO: add path latter
			std::string headerPath;
			std::string srcIncludeStr = "#include \"../generatedHeader/" + proc->getName() + ".h\"\n";
			return srcIncludeStr;
		}

        std::string  CCodeGenerator::generateSrcMethods(Process* proc)
		{		
			std::string outStr = "";
			/*code generation for base methods*/
			std::cout << "generate Methods" << std::endl;
			for (Method* m : proc->getMethods())
			{
				if(m->getAlgorithmId().compare(""))
				{
					std::string rttStr =  m->getReturnType()->getName();
					std::string classNamespace = proc->getName() + "::";
					std::string methodName = m->getName();
					std::string attrStr = "(";
					int i = 1;
					for (Attribute* a : m->getAttributes()) 
					{
						std::string termStr = a->getType()->getName() + " " + a->getIdentifier();
						attrStr += termStr;
						if (i < m->getAttributes().size()) 
						{
							attrStr += ", ";
						}
						i++;
					}
					attrStr += ")";
					std::string methodDef = rttStr + " " + classNamespace + methodName + attrStr;
					std::string returnVal = "\t" + rttStr + " result;" + CR;
					std::string ret = "\treturn result;\n";
					std::string methodBody = "{\n" + returnVal + ret + "\n}\n";
					outStr += (methodDef + methodBody);
				}
			}
			std::cout << "generate Methods Over" << std::endl;
			/*code generation for communication methods*/
			std::cout << "generate Communication Methods" << std::endl;
			for (CommMethod* m : proc->getCommMethods()){
				//std::string rttStr = m->getReturnType()->getName();
				std::string rttStr = "int";
				std::string classNamespace = proc->getName() + "::";
				std::string methodName = m->getName();
				std::string attrStr = "(";
				int i = 1;
				for (Attribute* a : m->getAttributes()) 
				{
					std::string termStr = a->getType()->getName() + " " + a->getIdentifier();
					attrStr += termStr;
					if (i < m->getAttributes().size()) 
					{
						attrStr += ", ";
					}
					i++;
				}
				attrStr += ")";
				std::string methodDef = rttStr + " " + classNamespace + methodName + attrStr;
				std::string returnVal = rttStr + " result;" + CR;
				std::string ret = "return result;\n";
				std::string commStr = "";
				if(!m->getCommId().compare("ether")){
					commStr += "/*Refine your Implementation here*/\n";
					commStr += "int length_ = 0;\n";
					commStr += "u_char* data_ = (u_char*)malloc(length_*sizeof(u_char));\n";
					commStr += "u_char* dst_;";
					if(m->getInOut()){
						//IN
						commStr += "/*Add MAC Address here*/\n";
						commStr += "ushort mac[6];\n";
						commStr += "EtherReceiver er = new EtherReceiver();\n";
						commStr += "pcap_if_t* dev = er->getDevice();\n";
						commStr += "/*Add self defined dataHandler to handle data received*/\n";
						commStr += "/*parameters: u_char* param, const struct pcap_pkthdr* header, const u_char* packetData*/";
						commStr += "er.listenWithHandler(dev, dataHandler);\n";
					} else {
						//OUT
						commStr += "/*Add MAC Address here*/\n";
						commStr += "ushort mac[6];\n";
						commStr += "EtherSender snd = new EtherSender(mac);\n";
						commStr += "/*Add data and length to send*/\n";
						commStr += "int length;\n";
						commStr += "int success = snd.sendEtherBroadcast(data_, length);\n";
					}
					
				} else if(!m->getCommId().compare("UDP")){
					if(m->getInOut()){
						commStr += "/*Add IP Str and portNUm here*/\n";
						commStr += "std::string IPStr_;\n";
						commStr += "u_short portNum_;\n";
						commStr += "UDPReceiver  er = new UDPReceiver();\n";
						commStr += "/*allocation for dst_ here*/\n";
						commStr += "er.receivePacket(dst_, IPStr_, portNum_);\n";
					} else {
						commStr += "/*Add Ip Str and portNum here*/\n";
						commStr += "std::string IPStr_;\n";
						commStr += "u_short portNum_;\n";
						commStr += "UDPSender snd = new UDPSender();\n";
						commStr += "/*Add length and data content here*/\n";
						commStr += "snd.sendPacket(data_, length_, IPStr_, portNum_);\n";
					}
				} else {
					std::cout << "Invalid commway num." << std::endl;
				}

				std::string methodBody = "{\n" + commStr + returnVal + ret + "\n}\n";
				outStr += (methodDef + methodBody);
			}
			std::cout << "generate Communication Methods Over" << std::endl;

			std::cout << "generate Crypt Methods" << std::endl;
			for(Method* m : proc->getMethods())
			{
				std::string rttStr =  m->getReturnType()->getName();
				std::string classNamespace = proc->getName() + "::";
				std::string methodName = m->getName();
				std::string attrStr = "(";
				int i = 1;
				for (Attribute* a : m->getAttributes()) 
				{
					std::string termStr = a->getType()->getName() + " " + a->getIdentifier();
					attrStr += termStr;
					if (i < m->getAttributes().size()) 
					{
						attrStr += ", ";
					}
					i++;
				}
				attrStr += ")";
				std::string methodDef = rttStr + " " + classNamespace + methodName + attrStr;
				std::string returnVal = rttStr + " result;" + CR;
				std::string ret = "return result;\n";
				std::string cryptStr = "";
				std::string methodBody = "{\n" + cryptStr + returnVal + ret + "\n}\n";
				if(m->getAlgorithmId().compare(""))
				{
					cryptStr += "/*Add your input data here*/\n";
					cryptStr += "/*Configure the mod and the length of the cryptLib*/\n";
					cryptStr += "int length_;\n";
					cryptStr += "int mod_ = -1;\n";
					cryptStr += "char* in_ = (char*)malloc(sizeof(char)*length);\n";
					cryptStr += "char* out_;\n";
					cryptStr += "/*configure the key*/\n";
					cryptStr += "char* key_;\n";
					cryptStr += "Cryptor crypt = new Cryptor();\n";
					cryptStr += "crypt.crypt(in_, key_, length_, out_, mod_);\n";					
				}
				outStr += (methodDef + methodBody);
			}
			
			std::cout << "generate Crypt Methods Over" << std::endl;
			return outStr;
		}

        std::string CCodeGenerator::generateMain(Process* proc)
		{
			std::string outStr = "";
			// current state 
			outStr += "int __currentState = STATE__" + proc->getStateMachines().front()->getStartVertex()->getName()+ ";\n";
			
			outStr += "int main(int argc, char** argv) {\n";
			outStr += generateSMLoop(proc);
			outStr += "}\n";
			return outStr;
		}

        //std::string  CCodeGenerator::generateGuardVarsDef(Process* proc);
        std::string  CCodeGenerator::generateSMLoop(Process* proc)
		{
			std::string outStr = "";
			std::cout << "generateSMLoopMain" << std::endl;
			outStr += "while(__currentState != STATE__" + proc->getStateMachines().front()->getEndVertex()->getName()+ ") {\n";
			outStr += "\tswitch(__currentState){\n";
			//make sure that start state is included
			//TODO
			outStr += this->generateStateBehavior((StateMachine *)proc->getStateMachines().front());
			outStr += "\t\tdefault: break;\n";
			outStr += "\t}\n";
			outStr += "}\n";
			std::cout << "generateSMLoopMain Over" << std::endl;
			
			std::cout << "generateSMLoopOther" << std::endl;
			std::cout << "SM size: " << proc->getStateMachines().size() << std::endl;
			if(proc->getStateMachines().size() > 1){
				int stateMachineId = 1;
				std::list<StateMachine*> sms = proc->getStateMachines();
				for(std::list<StateMachine*>::iterator it = (++sms.begin()); it != sms.end(); ++it){
					std::string stateMachineFunctionStr = "void stateMachine" + std::to_string(stateMachineId) + "Behavior(){\n";
					stateMachineFunctionStr += "int __sm" + std::to_string(stateMachineId) + "State = " + "STATE__"+(*it)->getStartVertex()->getName() + ";\n";

					stateMachineFunctionStr += "while(__sm" + std::to_string(stateMachineId) + "State != " + (*it)->getEndVertex()->getName() + "){\n";
					stateMachineFunctionStr += "\tswitch(__sm" + std::to_string(stateMachineId) + "State){\n";
					std::cout << "HERE"<< stateMachineId << std::endl;
					stateMachineFunctionStr += this->generateStateBehavior((*it));
					std::cout << "HERE" << std::endl;
					stateMachineFunctionStr += "\t}\n";
					stateMachineFunctionStr += "\t\tdefault: break;\n";
					stateMachineFunctionStr += "\t}\n";
					stateMachineFunctionStr += "}\n";
					outStr += stateMachineFunctionStr + "\n";
					stateMachineId ++;
				}
			}
			std::cout << "generateSMLoopOther Over" << std::endl;
			return outStr;
		}

		std::string CCodeGenerator::generateStateBehavior(StateMachine* sm)
		{
			std::string casesBody;
			std::string caseTab = "\t\t";
			std::string caseBodyTab = "\t\t\t";
			
			std::cout << "GenStateBehave" << std::endl;
			for(Vertex* v : sm->getVertices()){
				
				std::cout << "vertex " + v->getName() << std::endl;
				casesBody += (caseTab + "STATE__" + v->getName() + ":") + CR;
				bool elseIf = false;
				for(Edge* e : sm->getEdges()){
					std::cout << "edge loop" << std::endl;
					if(!e->getFromVertex()->getName().compare(v->getName())){
						// if the edge starts from v
						// makesure Make sure guard to string method
						std::cout << e->getFromVertex()->getName() << v->getName() << std::endl;
						if(e->getGuard() != nullptr){
							casesBody += (caseBodyTab + (elseIf ? "else if(" : "if(") + e->getGuard()->to_string() + "){") + CR;
						} 
						
						std::cout << "caseBody"<< std::endl;
						elseIf = true;
						for(Action* a : e->getActions()){
							casesBody += TAB + (caseBodyTab + a->to_string() + ";") + CR;
						}
						casesBody += (caseBodyTab + "}") + CR;
					}
					
					std::cout << "edge loop end" << std::endl;
				}
			}
			std::cout << "GenStateBehave Over" << std::endl;
			return casesBody;
		}
        /*-------------Generate UserTypes-------------*/
		
		std::string CCodeGenerator::generateUserTypes(std::string path, Model* model)
		{
			std::ofstream outUserTypeFile;
		    //TODO: make sure here
		    std::string fileName = "UserType.h";
		    std::string outStr = "";
			for(UserType* u : model->getUserTypes()){
				//make sure 
				outStr += ("class " + u->getName() + "{") + CR;
				outStr += "\tpublic:\n";
				for(Attribute* a : u->getAttributes()){
					outStr += "\t\t" + (a->getType()->getName() + " " + a->getIdentifier()) + "\n";
				}
				outStr += "};\n";
			}
			outUserTypeFile.open(path + "\\" + fileName);
			outUserTypeFile << outStr << std::endl;
			outUserTypeFile.close();
		}

		/*---------Gen---------*/
        void  CCodeGenerator::generateCodeProc(std::string path, Process* proc)
		{
			this->generateHeaderFile(path, proc);
			this->generateSrcFile(path, proc);
			//this->generateUserTypes(path, proc->getModel());
		}


        void CCodeGenerator::generateAll(std::string path, Model* model)
		{
			for(Process* proc : model->getProcesses())
			{
				this->generateCodeProc(path, proc);
			}
		}


        //constructors
         CCodeGenerator::CCodeGenerator(/*args*/)
         {

         }

         CCodeGenerator::~CCodeGenerator()
         {

         }
    
}
