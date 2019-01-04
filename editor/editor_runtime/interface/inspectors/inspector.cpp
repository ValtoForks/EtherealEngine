#include "inspector.h"

void Tooltip(const rttr::property& prop)
{
	auto& g = *gui::GetCurrentContext();
	if(!g.DragDropActive && gui::IsItemHovered())
	{
		gui::SetMouseCursor(ImGuiMouseCursor_Help);
		auto tooltip = prop.get_metadata("tooltip");
		if(tooltip)
		{
			gui::BeginTooltip();
			gui::TextUnformatted(tooltip.to_string().c_str());
			gui::EndTooltip();
		}
	}
}

void Tooltip(const std::string& tooltip)
{
	auto& g = *gui::GetCurrentContext();
	if(!g.DragDropActive && gui::IsItemHovered())
	{
		gui::SetMouseCursor(ImGuiMouseCursor_Help);
		gui::BeginTooltip();
		gui::TextUnformatted(tooltip.c_str());
		gui::EndTooltip();
	}
}
property_layout::property_layout(const rttr::property& prop, bool columns /*= true*/)
{
	std::string pretty_name = prop.get_name().to_string();
	auto meta_pretty_name = prop.get_metadata("pretty_name");
	if(meta_pretty_name)
	{
		pretty_name = meta_pretty_name.get_value<std::string>();
	}

	if(columns)
	{
		if(gui::GetColumnsCount() > 1)
		{
			gui::EndColumns();
		}
		gui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
	}

	gui::AlignTextToFramePadding();
	gui::TextUnformatted(pretty_name.c_str());

	Tooltip(prop);

	gui::NextColumn();

	gui::PushID(pretty_name.c_str());
	gui::PushItemWidth(gui::GetContentRegionAvailWidth());
}

property_layout::property_layout(const std::string& name, bool columns /*= true*/)
{
	if(columns)
	{
		if(gui::GetColumnsCount() > 1)
		{
			gui::EndColumns();
		}
		gui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
	}

	gui::AlignTextToFramePadding();
	gui::TextUnformatted(name.c_str());

	gui::NextColumn();

	gui::PushID(name.c_str());
	gui::PushItemWidth(gui::GetContentRegionAvailWidth());
}

property_layout::property_layout(const std::string& name, const std::string& tooltip, bool columns /*= true*/)
{
	if(columns)
	{
		if(gui::GetColumnsCount() > 1)
		{
			gui::EndColumns();
		}
		gui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
	}

	gui::AlignTextToFramePadding();
	gui::TextUnformatted(name.c_str());

	Tooltip(tooltip);

	gui::NextColumn();

	gui::PushID(name.c_str());
	gui::PushItemWidth(gui::GetContentRegionAvailWidth());
}

property_layout::~property_layout()
{
	gui::PopItemWidth();
	gui::PopID();
	if(gui::GetColumnsCount() > 1)
	{
		gui::EndColumns();
	}
}
