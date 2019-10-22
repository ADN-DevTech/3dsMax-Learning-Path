#pragma once

#include <maxapi.h>
#include <Qt/QMaxParamBlockWidget.h>
#include "ui_plugin_form.h"

namespace Ui
{
	class PluginRollup;
}

class QtPluginRollup : public MaxSDK::QMaxParamBlockWidget
{
	// This is a macro that connects this class to the Qt build system
	Q_OBJECT

public:
	explicit QtPluginRollup(QWidget* parent = nullptr);
	~QtPluginRollup(void);

	// Required by QMaxParamBlockWidget:
	virtual void SetParamBlock(ReferenceMaker* /*owner*/, IParamBlock2* const /*param_block*/) override {};
	virtual void UpdateUI(const TimeValue t) override
	{
		Interface* ip = GetCOREInterface();
		ip->RedrawViews(t, REDRAW_NORMAL);
	};
	virtual void UpdateParameterUI(const TimeValue /*t*/, const ParamID /*param_id*/, const int /*tab_index*/) override {};

protected slots:
	void on_pushButton_clicked();

private:
	Ui::PluginRollup* ui;
};
