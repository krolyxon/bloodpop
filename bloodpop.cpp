#include "bloodpop.h"
#include "patient.h"

#include "imgui/imgui.h"
#include <cstdio>
#include <string>

const char *genders[] = {"Male", "Female"};
const char *groups[] = {"A+", "A-", "B+", "B-", "Ab+", "Ab-", "O+", "O-"};
const char *types[] = {"Donor", "Reciever"};
static ImGuiTableFlags flags =
    ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg |
    ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable |
    ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

static ImGuiWindowFlags wflags =
    // ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

Patient patients[MAX];
static int n = readdb(patients);

namespace BloodPop {
void RenderUI() {
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  bool p_open = true;

  ImGui::Begin("BloodPop", &p_open, wflags);

  if (ImGui::BeginTabBar("##Lavda")) {
    if (ImGui::BeginTabItem("Patients")) {

      ImGui::BeginTable("Patients", 6, flags);
      ImGui::TableSetupColumn("Sr. No.", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Age", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Gender", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableSetupColumn("Blood Group",
                              ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableHeadersRow();

      for (int i = 0; i < n; i++) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", i + 1);
        ImGui::TableNextColumn();
        ImGui::Text("%s", patients[i].name.c_str());
        ImGui::TableNextColumn();
        ImGui::Text("%d", patients[i].age);
        ImGui::TableNextColumn();
        ImGui::Text("%s", patients[i].gender.c_str());
        ImGui::TableNextColumn();
        ImGui::Text("%s", (get_patient_type(patients[i].type)));
        ImGui::TableNextColumn();
        ImGui::Text("%s", get_blood_group(patients[i].group));
      }

      ImGui::EndTable();

      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Add Patient")) {
      ImGui::SeparatorText("Enter Patient Details");
      static char name[128] = "";
      static int age = 18;
      static int type_current = 0;
      static int gender_current = 0;
      static int group_current = 0;

      ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
      ImGui::Combo("Patient Type", &type_current, types, IM_ARRAYSIZE(types));
      ImGui::Combo("Gender", &gender_current, genders, IM_ARRAYSIZE(genders));
      ImGui::Combo("BloodGroup", &group_current, groups, IM_ARRAYSIZE(groups));
      ImGui::InputInt("Age", &age);

      if (ImGui::Button("Save Patient to Database")) {
        patients[n].name = name;
        patients[n].gender = genders[gender_current];
        patients[n].type = get_patient_type_enum(type_current);
        patients[n].age = age;
        patients[n].group = get_blood_group_enum(group_current);
        ImGui::Text("%s", patients[n + 1].name.c_str());
        ImGui::Text("%s", get_patient_type(patients[n + 1].type));
        ImGui::Text("%s", get_blood_group(patients[n + 1].group));
        ImGui::Text("%d", age);
        ImGui::Text("%s", patients[n + 1].gender.c_str());
        writedb(patients, n);
        n = readdb(patients);
      }
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  // ImGui::ShowDemoWindow();
  ImGui::End();
}
} // namespace BloodPop
