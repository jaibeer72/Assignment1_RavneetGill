
//
//  main.cpp
//  SharesProject
//
//  Created by Ravneet Kaur Batth on 27/02/23.
//
#include "Stack.h"
#include "Queue.h"

int main()
{
    Stack lifo;
    Queue fifo;
    
    while (true)
    {
        char option;
        cout << "\nSelect Option:\nEnter 1 to add a stock purchase, \n2 to query a stock, \n3 to sell a stock, \nor 0 to exit: ";
        cin >> option;
        
        if (option == '0') break;
        
        if (option == '1') { // Add stock purchase
            string name;
            int shares;
            double price;
            cout << "Enter name of stock: ";
            cin >> name;
            cout << "Enter number of shares purchased: ";
            cin >> shares;
            cout << "Enter price per share: $";
            cin >> price;
            
            Stock s = {name, shares, price};
            lifo.push(s);
            fifo.enqueue(s);
        }
        else if (option == '2') { // Query stock
            string name;
            int shares;
            cout << "Enter name of stock: ";
            cin >> name;
            cout << "Enter number of shares in question: ";
            cin >> shares;
            
            double lifo_total_price = 0, fifo_total_price = 0;
            int lifo_shares_left = shares, fifo_shares_left = shares;
            bool lifo_found = false, fifo_found = false;
            
            // Calculate LIFO price and shares left
            Stack lifo_temp = lifo;
            while (!lifo_temp.isEmpty()) {
                Stock s = lifo_temp.peekStack();
                if (s.name == name) {
                    lifo_found = true;
                    if (lifo_shares_left >= s.shares) {
                        lifo_total_price += s.price * s.shares;
                        lifo_shares_left -= s.shares;
                    }
                    else {
                        lifo_total_price += s.price * lifo_shares_left;
                        lifo_shares_left = 0;
                        break;
                    }
                }
                lifo_temp.pop();
            }
            
            // Calculate FIFO price and shares left
            Queue fifo_temp = fifo;
            while (!fifo_temp.isEmpty()) {
                Stock s = fifo_temp.peekQueue();
                if (s.name == name) {
                    fifo_found = true;
                    if (fifo_shares_left >= s.shares) {
                        fifo_total_price += s.price * s.shares;
                        fifo_shares_left -= s.shares;
                    }
                    else {
                        fifo_total_price += s.price * fifo_shares_left;
                        fifo_shares_left = 0;
                        break;
                    }
                }
                fifo_temp.dequeue();
            }
            
            if (!lifo_found)
                cout << "ERROR: Stock not found in Inventory!\n";
            else if (lifo_shares_left>0)
                cout << "ERROR: You do not own " <<shares<<" shares of this company!\n";
            else    {
                cout << "LIFO average price per share: $" << lifo_total_price / shares << endl;
                cout << "FIFO average price per share: $" << fifo_total_price / shares << endl;
            }
        }
        
                else if (option == '3') { // Sell stock
                string name;
                int shares1, shares2;
                cout << "Enter name of stock to sell: ";
                cin >> name;
                cout << "Enter number of shares to sell: ";
                cin >> shares1;
                shares2 = shares1;
                bool no_sale = false;
                
                // Remove shares from LIFO stack
                Stack lifo_temp, lifo_nosale;
                bool lifo_found = false;
                while (!lifo.isEmpty()) {
                    Stock s = lifo.peekStack();
                    
                    if (s.name == name) {
                            lifo_found = true;
                            if (s.shares <= shares1) {
                                shares1 -= s.shares;
                                lifo_nosale.push(s);
                                lifo.pop();

                            }
                            else {
                                s.shares -= shares1;
                                shares1 = 0;
                                lifo_temp.push(s);
                                lifo_nosale.push(s);
                                lifo.pop();
                                break;
                            }
                    }
                    else {
                        lifo_temp.push(s);
                        lifo_nosale.push(s);
                        lifo.pop();
                    }
                }
                if((shares1>0)||(!lifo_found))
                {
                    no_sale = true;
                    cout << "\nERROR: You either don't own this stock or do not have enough shares to sell.";
                    while (!lifo_nosale.isEmpty()) {
                        lifo.push(lifo_nosale.peekStack());
                        lifo_nosale.pop();
                    }
                }
                else
                {
                    while (!lifo_temp.isEmpty()) {
                        lifo.push(lifo_temp.peekStack());
                        lifo_temp.pop();
                    }
                }
                
                // Remove shares from FIFO queue
                Queue fifo_temp;
                
                //bool fifo_found = false;
                while ((!fifo.isEmpty())&&(no_sale!=true)) {
                    Stock s = fifo.peekQueue();
                    
                    if (s.name == name) {
                       // fifo_found = true;
                        if (s.shares <= shares2) {
                            shares2 -= s.shares;
                            fifo.dequeue();
                        }
                        else {
                            s.shares -= shares2;
                            shares2 = 0;
                            fifo_temp.enqueue(s);
                            fifo.dequeue();
                        }
                    }
                    else {
                        fifo_temp.enqueue(s);
                        fifo.dequeue();
                    }
                }
                
                while (!fifo_temp.isEmpty()) {
                    fifo.enqueue(fifo_temp.peekQueue());
                    fifo_temp.dequeue();
                    
                }
               // if (!fifo_found) cout << "Stock not found in FIFO queue!\n";
 
                // Display remaining stock inventory
                cout << "\n\nRemaining stock inventory:\n\nLIFO Method\n";
                Stack lifo_temp2 = lifo;
                while (!lifo_temp2.isEmpty()) {
                    Stock s = lifo_temp2.peekStack();
                    cout << s.name << " " << s.shares << " shares at $" << s.price << endl;
                    lifo_temp2.pop();
                }
                cout << "\nFIFO Method\n";
                Queue fifo_temp2 = fifo;
                while (!fifo_temp2.isEmpty()) {
                    Stock s = fifo_temp2.peekQueue();
                    cout << s.name << " " << s.shares << " shares at $" << s.price << endl;
                    fifo_temp2.dequeue();
                    
                }
            }
            else {
                cout << "Invalid option entered!\n";
            }
    }
 
    return 0;
 }
