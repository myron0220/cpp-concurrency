/*
  detaching a thread to handle other documents
*/

#include <string>

void edit_document(const std::string& filename) {
  open_document_and_display_gui(filename); // assume this will not modify the filename

  while (!done_editing) {
    user_command cmd = get_user_input();

    if (cmd.type == open_new_document) {
      const std::string new_name = get_filename_from_user();

      // create a new thread and detach it
      std::thread t(edit_document, std::ref(new_name));
      t.detach();
    } else {
      process_user_input(cmd);
    }
  }
}
