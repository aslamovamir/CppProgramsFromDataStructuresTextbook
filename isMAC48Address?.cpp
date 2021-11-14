// A media access control address (MAC address) is a unique identifier assigned to network interfaces for communications on the physical network segment.

// The standard (IEEE 802) format for printing MAC-48 addresses in human-friendly form is six groups of two hexadecimal digits (0 to 9 or A to F),
// separated by hyphens (e.g. 01-23-45-67-89-AB).

// Your task is to check by given string inputString whether it corresponds to MAC-48 address or not.

// Example

// For inputString = "00-1B-63-84-45-E6", the output should be
// isMAC48Address(inputString) = true;
// For inputString = "Z1-1B-63-84-45-E6", the output should be
// isMAC48Address(inputString) = false;
// For inputString = "not a MAC-48 address", the output should be
// isMAC48Address(inputString) = false.

bool isMAC48Address(string inputString) {
    int num_hyphens = 0;
    int num_digs = 0;
    if (inputString[0] == '-' || inputString[inputString.size()-1] == '-') {
        return false;
    } else {
        for (auto itr: inputString) {
            cout<<itr<<" ";
            if (itr == '-') {
                num_hyphens++;
                if (num_digs != 2) {
                    return false;
                }
                num_digs = 0;
                if (num_hyphens > 5) { return false; }
            }
            else if (isdigit(itr)) { 
                num_digs++;
                if (num_digs > 2) {
                    return false;
                }
                continue; 
            }
            else {
                if (itr >= 'A' && itr <= 'F') {
                    num_digs++;
                    if (num_digs > 2) {
                        return false;
                    }
                    continue;
                } else { return false; } 
            }
        }
    }
    if (num_hyphens != 5 || num_digs != 2) {
        return false;
    } else {
        return true;
    }
}
