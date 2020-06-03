#pragma once

#include <vector>
#include <stack>
#include <string>
#include "Core/mvAppItem.h"


namespace Marvel {

	class mvApp final
	{

	public:

		static mvApp* GetApp();

		void render();

		//-----------------------------------------------------------------------------
		// Basic AppItems
		//-----------------------------------------------------------------------------

		mvAppItem* addInputText   (const std::string& parent, const std::string& name, const std::string& hint = "");
		mvAppItem* addRadioButtons(const std::string& parent, const std::string& name, const std::vector<std::string>& itemnames, int default_value = 0);
		mvAppItem* addButton      (const std::string& parent, const std::string& name);

		//-----------------------------------------------------------------------------
		// Tabs
		//-----------------------------------------------------------------------------

		mvAppItem* addTabBar(const std::string& parent, const std::string& name);
		mvAppItem* addTab   (const std::string& parent, const std::string& name);
		mvAppItem* endTab   (const std::string& parent);
		mvAppItem* endTabBar(const std::string& parent);

		//-----------------------------------------------------------------------------
		// Adding Menus
		//-----------------------------------------------------------------------------

		mvAppItem* addMenuBar (const std::string& name);
		mvAppItem* addMenu    (const std::string& parent, const std::string& name);
		mvAppItem* addMenuItem(const std::string& parent, const std::string& name);
		mvAppItem* endMenu    (const std::string& parent);
		mvAppItem* endMenuBar (const std::string& parent);

		//-----------------------------------------------------------------------------
		// Groups
		//-----------------------------------------------------------------------------

		mvAppItem* addGroup(const std::string& parent, const std::string& name);
		mvAppItem* endGroup(const std::string& parent);

		//-----------------------------------------------------------------------------
		// Child Window
		//-----------------------------------------------------------------------------

		mvAppItem* addChild(const std::string& parent, const std::string& name, int width, int height);
		mvAppItem* endChild(const std::string& parent);

		//-----------------------------------------------------------------------------
		// Misc Items
		//-----------------------------------------------------------------------------

		mvAppItem* addCollapsingHeader(const std::string& parent, const std::string& name);
		mvAppItem* addSpacing         (const std::string& parent, int count = 1);
		mvAppItem* addSameLine        (const std::string& parent, float offsetx = 0.0f, float spacing = -1.0f);
		mvAppItem* addTooltip         (const std::string& parent, const std::string& name);
		mvAppItem* endTooltip         (const std::string& parent);

		//-----------------------------------------------------------------------------
		// Two-step Item modifications
		//-----------------------------------------------------------------------------
		void setItemCallback(const std::string& name, const std::string& callback);
		void setItemWidth   (const std::string& name, int width);
		void setItemTip     (const std::string& name, const std::string& tip);

		//-----------------------------------------------------------------------------
		// Parent stack operations
		//-----------------------------------------------------------------------------
		void       pushParent(mvAppItem* item);
		mvAppItem* popParent();
		mvAppItem* topParent();

		//-----------------------------------------------------------------------------
		// Callbacks
		//-----------------------------------------------------------------------------
		void setMainCallback(const std::string& callback) { m_callback = callback; }
		void triggerCallback(const std::string& name, const std::string& sender);

		//-----------------------------------------------------------------------------
		// Utilities
		//-----------------------------------------------------------------------------
		mvAppItem* getItem(const std::string& name);
		void       setModuleDict  (PyObject* dict) { m_pDict = dict; }
		void       setSize(unsigned width, unsigned height) { m_width = width; m_height = height; }

	private:

		mvApp() = default;

		mvApp(const mvApp& other) = delete;
		mvApp(mvApp&& other) = delete;
		mvApp operator=(const mvApp& other) = delete;
		mvApp operator=(mvApp&& other) = delete;

		bool doesParentAllowRender(mvAppItem* item);


	private:

		static mvApp*           s_instance;
		std::vector<mvAppItem*> m_items;
		std::stack<mvAppItem*>  m_parents;
		PyObject*               m_pDict;
		unsigned                m_width;
		unsigned                m_height;
		std::string             m_callback;

	};

}