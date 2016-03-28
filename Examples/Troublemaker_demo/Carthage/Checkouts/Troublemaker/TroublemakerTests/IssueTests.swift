//
//  IssueTypeTests.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/23/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

import Quick
import Nimble
@testable import Troublemaker

class IssueTests : QuickSpec {
    override func spec() {
        describe("Issue") {
            it("should be of Warning and Error types") {
                let data = IssueData(title: "test")
                expect(Issue.Error(data)).notTo(beNil())
                expect(Issue.Warning(data)).notTo(beNil())
            }
            
            it("should return issue data") {
                let data = IssueData(title: "test")
                expect(data).to(equal(Issue.Warning(data).data))
                expect(data).to(equal(Issue.Error(data).data))
            }
            
            context("when initialized with a valid issue log") {
                
                let title = "Here is issue title"
                let filePath = "/Path/to/file.txt"
                let line: UInt = 12
                let column: UInt = 2
                
                it("should be of corect issue type") {
                    let data = IssueData(title: title)
                    
                    let warningLog = "warning: \(title)"
                    let warning = Issue(log: warningLog)
                    expect(warning!).to(equal(Issue.Warning(data)))
                    
                    let errorLog = "error: \(title)"
                    let error = Issue(log: errorLog)
                    expect(error!).to(equal(Issue.Error(data)))
                }
                
                it("should set title to data") {
                    let log = "warning: \(title)"
                    let issue = Issue(log: log)
                    expect(issue?.data.title).to(equal(title))
                }
                
                it("should set file path to data") {
                    let log = "\(filePath): warning: \(title)"
                    let issue = Issue(log: log)
                    expect(issue?.data.filePath).to(equal(filePath))
                }
                
                it("should set line to data") {
                    let log = "\(filePath):\(line): warning: \(title)"
                    let issue = Issue(log: log)
                    expect(issue?.data.line).to(equal(line))
                }
                
                it("should set column to data") {
                    let log = "\(filePath):\(line):\(column): warning: \(title)"
                    let issue = Issue(log: log)
                    expect(issue?.data.column).to(equal(column))
                }
            }
            
            context("when initialized with an invalid issue log") {
                
                it("should return nil") {
                    expect(Issue(log: "Here is an invalid warning log:3 ")).to(beNil())
                    expect(Issue(log: "dissaster: is an invalid warning log")).to(beNil())
                }
                
            }
            
            context("when compared to another issue") {
                
                let data = IssueData(title: "test")
                let comparedIssue = Issue.Warning(data)
                
                it("should be equal to a similar Issue") {
                    expect(comparedIssue).to(equal(Issue.Warning(data)))
                }
                
                it("should NOT be equal to a issue of a different type") {
                    expect(comparedIssue).notTo(equal(Issue.Error(data)))
                }
            }
        }
    }
}
