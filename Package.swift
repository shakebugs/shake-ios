// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Shake",
    platforms: [.iOS(SupportedPlatform.IOSVersion.v11)],
    products: [
        .library(
            name: "Shake",
            targets: ["Shake"]),
    ],
    targets: [
        .binaryTarget(name: "Shake",
                      path: "./Sources/Shake.xcframework")
    ]
)
