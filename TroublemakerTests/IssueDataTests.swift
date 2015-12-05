//
//  IssueDataTests.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/23/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

import Quick
import Nimble
@testable import Troublemaker

class IssueDataTests : QuickSpec {
    override func spec() {
        describe("IssueData") {
            
            let title = "Test title"
            let filePath = "/Path/to/test/file.txt"
            let line: UInt = 1
            let column: UInt? = nil
            let comparedData = IssueData(title: title, filePath: filePath, line: line, column: column)

            it("should be equal to a similar data") {
                let similatData = IssueData(title: title, filePath: filePath, line: line, column: column)
                expect(comparedData).to(equal(similatData))
            }
            
            it("should not be equal to a different data") {
                let differentTitleData = IssueData(title: "bla bla", filePath: filePath, line: line, column: column)
                expect(comparedData).notTo(equal(differentTitleData))
                
                let differentFilePathData = IssueData(title: title, filePath: "wrongPath", line: line, column: column)
                expect(comparedData).notTo(equal(differentFilePathData))
                
                let differentLineData = IssueData(title: title, filePath: filePath, line: 3, column: column)
                expect(comparedData).notTo(equal(differentLineData))
                
                let differentColumnData = IssueData(title: title, filePath: filePath, line: line, column: 3)
                expect(comparedData).notTo(equal(differentColumnData))
            }
        }
    }
}
