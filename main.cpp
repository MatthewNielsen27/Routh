

#include <iostream>
#include <vector>


using namespace std;


template<typename T>
void print_matrix(const vector<vector<T>>& mat) {
    for (const auto& row : mat) {
        for (const auto& value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
}


int main() {
    static const vector<int>& coeff = {1, 2, 5, 4, 9};
    const size_t row_size = coeff.size() / 2 + 1;

    // Create matrix to hold value
    vector<vector<int>> mat;
    mat.reserve(coeff.size());

    for (auto& row : mat) {
        row.reserve(row_size);
    }

    // Create first 2 rows
    mat.emplace_back();
    mat.emplace_back();

    // Fill in the top 2 rows
    bool toggle = 0;
    for (const auto& value : coeff) {
        if (toggle == 0) {
            mat[0].push_back(value);
        } else {
            mat[1].push_back(value);
        }

        toggle = !toggle;
    }

    mat[0].push_back(0);
    for (size_t i = 0; i <= mat[0].size() - mat[1].size(); ++i) {
        mat[1].push_back(0);
    }

    // Compute the next n rows

    auto remaining_rows = coeff.size() - 2;

    for (size_t i = mat.size(); i < coeff.size(); ++i) {
        size_t b = mat.size() - 1;
        size_t a = mat.size() - 2;
        
        mat.emplace_back();     // add the next row

        for (size_t val_i = 0; val_i < mat[b].size(); ++val_i) {
            auto b1 = mat[b][0];                    // first value in prev row
            auto a1 = mat[a][0];                    // first value in prev prev row
            auto b2 = mat[b][val_i + 1];            // column value in prev row
            auto a2 = mat[a][val_i + 1];            // column value in prev prev row

            // cout << "(" << b1 << " * " << a2 << ") - (" << a1 << " * " << b2 << ") / " << b1 << endl;

            auto val = ((b1 * a2) - (a1 * b2) ) / b1;
            
            mat[i].push_back(val);

            if (val == 0 || i == coeff.size() - 1) {
                break;
            }
        }
    }

    print_matrix(mat);

    // Determine stability

    bool prev_sign = coeff[coeff.size() - 1] > 0;
    int sign_changes = 0;
    int zeros_found = 0;

    for (size_t row_i = 2; row_i < coeff.size(); ++row_i) {
        auto column_limit = (row_i == coeff.size() - 1) ? 1 : mat[row_i].size() - 1;

        for (size_t val_i = 0; val_i < column_limit; ++val_i) {
            auto val = mat[row_i][val_i];
            auto sign = val > 0;

            if (val == 0) {
                // cout << "zero found at: " << row_i << "," << val_i << endl;

                zeros_found++;
            } else if (sign != prev_sign) {
                // cout << "Sign change at: " << row_i << "," << val_i << endl;
                sign_changes++;
            }

            prev_sign = sign;
        }
    }

    cout << "Sign changes: \t" << sign_changes << endl;
    cout << "Zeros found:  \t" << zeros_found << endl;

    cout << "Is the system stable? " << (bool) (zeros_found == 0 && sign_changes == 0) << endl;

    return 0;
}
