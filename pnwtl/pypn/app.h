/**
 * @file app.h
 * @brief Plugin Main Implementation
 * @author Simon Steele
 * @note Copyright (c) 2006 Simon Steele <s.steele@pnotepad.org>
 *
 * Programmers Notepad 2 : The license file (license.[txt|html]) describes 
 * the conditions under which this source may be modified / distributed.
 */
#ifndef app_h__included
#define app_h__included

/**
 * This class manages the environment for the plugin, storing
 * the links to IPN and acting as the main event sink.
 */
class App : 
	public extensions::IAppEventSink,
	public extensions::IScriptRunner
{
public:
	App(boost::python::handle<>& obj, extensions::IPN* app);

	virtual ~App();

	void Initialise();

// IAppEventSink
	virtual void OnNewDocument(extensions::IDocumentPtr doc);
	
// IScriptRunner
	virtual void RunScript(const char* name);
	virtual void RunDocScript(extensions::IDocumentPtr doc);

// Other
	void RegisterScript(const char* scriptname, const char* group, const char* name);

	extensions::IPN* GetPN() const;
	
	boost::python::object& PyModule();
	boost::python::object& PyNamespace();
	boost::python::object& PyPnGlue();

	void AddOutput(const char* text, int length = -1);

private:
	void loadInitScript();
	void runFile(const char* filename);
	
private:
	extensions::ITextOutput* m_output;
	extensions::IScriptRegistry* m_registry;
	extensions::IPN* m_app;
	boost::python::object main_module;
	boost::python::object main_namespace;
	boost::python::object m_glue;
};

extern App* g_app;

#endif // #ifndef app_h__included